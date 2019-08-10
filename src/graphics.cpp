#include "lfbg/graphics.h"

namespace lfbg {

// defined objects
GLuint __screen_texture_id__;
GLFWwindow* __window_handle__;
int __screen_width__, __screen_height__;
int __window_width__, __window_height__;
std::vector<color> __screen_buffer__;
color __foreground_color__ = COLOR::WHITE;
std::string __window_title__;
uint64_t __total_frames__;
window_helper __window__helper_obj__;

// extern objects
extern int __cursor_offset_x__, __cursor_offset_y__;
extern int __cursor_scale_x__, __cursor_scale_y__;
extern void init_fps();
extern void update_fps();
extern std::vector<color>& apply_palette(const std::vector<color>& buffer);

// ----------------------------------------------------------------------------
// callbacks
// ----------------------------------------------------------------------------

auto __default_window_resize_callback__ = [](int32_t w, int32_t h) {
    glfwGetFramebufferSize(__window_handle__, &__window_width__, &__window_height__);
    glViewport(0, 0, __window_width__, __window_height__);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ar = (double)(__window_width__) / __window_height__;
    const double oar = (double)(__screen_width__) / __screen_height__;
    ar /= oar;
    if (ar >= 1.0) {
        glOrtho(-ar, ar, -1, 1, 1, -1);
        __cursor_scale_x__ = std::ceil(h * oar);
        __cursor_scale_y__ = h;
        __cursor_offset_x__ = std::floor((w - __cursor_scale_x__) / 2);
        __cursor_offset_y__ = 0;
    } else {
        glOrtho(-1, 1, -1 / ar, 1 / ar, 1.0, -1.0);
        __cursor_scale_x__ = w;
        __cursor_scale_y__ = std::ceil(w / oar);
        __cursor_offset_x__ = 0;
        __cursor_offset_y__ = std::floor((h - __cursor_scale_y__) / 2);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
};

void set_default_window_resize_callback() {
    __window__helper_obj__.window_resize_callback = __default_window_resize_callback__;
}

// ----------------------------------------------------------------------------
// core
// ----------------------------------------------------------------------------

GLFWwindow* initgraph(int width, int height, float multiplier, RenderType rt, int swap_interval) {
    __screen_width__ = width;
    __screen_height__ = height;
    __screen_buffer__.resize(__screen_width__ * __screen_height__);

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "Error (" << error << "): " << description << std::endl;
    });

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    if (multiplier < 0) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        __window_handle__ = glfwCreateWindow(mode->width, mode->height, __window_title__.c_str(),
                                             glfwGetPrimaryMonitor(), NULL);
    } else if (multiplier == 0) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        __window_handle__ =
            glfwCreateWindow(mode->width, mode->height, __window_title__.c_str(), NULL, NULL);
        glfwMaximizeWindow(__window_handle__);
    } else {
        __window_handle__ =
            glfwCreateWindow(__screen_width__ * multiplier, __screen_height__ * multiplier,
                             __window_title__.c_str(), NULL, NULL);
    }
    if (!__window_handle__) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(__window_handle__, &__window__helper_obj__);

    set_default_window_resize_callback();
    glfwSetWindowSizeCallback(__window_handle__, [](GLFWwindow* handle, int32_t w, int32_t h) {
        auto obj = (window_helper*)glfwGetWindowUserPointer(handle);
        obj->window_resize_callback(w, h);
    });

    set_default_keyboard_callback();
    glfwSetKeyCallback(__window_handle__, [](GLFWwindow* handle, int k, int s, int a, int m) {
        auto obj = (window_helper*)glfwGetWindowUserPointer(handle);
        obj->keyboard_callback(k, s, a, m);
    });

    set_default_cursor_pos_callback();
    glfwSetCursorPosCallback(__window_handle__, [](GLFWwindow* handle, double x, double y) {
        auto obj = (window_helper*)glfwGetWindowUserPointer(handle);
        obj->cursor_pos_callback(x, y);
    });

    set_default_mouse_button_callback();
    glfwSetMouseButtonCallback(__window_handle__, [](GLFWwindow* handle, int b, int a, int m) {
        auto obj = (window_helper*)glfwGetWindowUserPointer(handle);
        obj->mouse_button_callback(b, a, m);
    });

    // glfwSetWindowAspectRatio(__window_handle__, __screen_width__, __screen_height__);
    glfwMakeContextCurrent(__window_handle__);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);

    glfwSwapInterval(swap_interval);

    glGenTextures(1, &__screen_texture_id__);
    glBindTexture(GL_TEXTURE_2D, __screen_texture_id__);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, __screen_width__, __screen_height__, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, __screen_buffer__.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (rt == RenderType::Retro) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    glActiveTexture(GL_TEXTURE0);

    glfwGetWindowSize(__window_handle__, &__window_width__, &__window_height__);
    __default_window_resize_callback__(__window_width__, __window_height__);
    init_fps();
    __total_frames__ = 0;
    return __window_handle__;
}

void closegraph() {
    glfwDestroyWindow(__window_handle__);
    glDeleteTextures(1, &__screen_texture_id__);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void bitblt() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (using_palette()) {
        auto buffer = apply_palette(__screen_buffer__);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, __screen_width__, __screen_height__, GL_BGRA,
                        GL_UNSIGNED_BYTE, buffer.data());
    } else {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, __screen_width__, __screen_height__, GL_BGRA,
                        GL_UNSIGNED_BYTE, __screen_buffer__.data());
    }
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);
    glTexCoord2f(1, 1);
    glVertex2f(1, -1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, -1);
    glEnd();
    glfwSwapBuffers(__window_handle__);
    kbreset();
    mbreset();
    glfwPollEvents();
    update_fps();
    __total_frames__++;
}

// ----------------------------------------------------------------------------
// basic drawing
// ----------------------------------------------------------------------------

void cleardevice(color c) { std::fill(__screen_buffer__.begin(), __screen_buffer__.end(), c); }

void putpixel(int x, int y, color c) {
    if (0 <= x && x < __screen_width__ && 0 <= y && y < __screen_height__)
        __screen_buffer__[y * __screen_width__ + x] = c;
}

color getpixel(int x, int y) {
    if (0 <= x && x < __screen_width__ && 0 <= y && y < __screen_height__)
        return __screen_buffer__[y * __screen_width__ + x];
    return -1;
}

void setcolor(color c) { __foreground_color__ = c; }

color getcolor() { return __foreground_color__; }

// ----------------------------------------------------------------------------
// info
// ----------------------------------------------------------------------------

bool closed() { return glfwWindowShouldClose(__window_handle__); }

std::pair<int, int> get_buffer_size() { return {__screen_width__, __screen_height__}; }

std::pair<int, int> get_window_size() { return {__window_width__, __window_height__}; }

// ----------------------------------------------------------------------------
// misc
// ----------------------------------------------------------------------------

void set_title(const std::string& title) {
    __window_title__ = title;
    glfwSetWindowTitle(__window_handle__, __window_title__.c_str());
}

const std::string& get_title() { return __window_title__; }

} // namespace lfbg