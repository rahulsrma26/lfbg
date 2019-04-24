#include "lfbg/graphics.h"

namespace lfbg {

GLuint __screen_texture_id__;
GLFWwindow* __window_handle__;
int __screen_width__, __screen_height__;
std::vector<color> __screen_buffer__;
std::string __window_title__;
bool __show_fps__ = true;
double __last_time__, __last_fps__;
int __frames_till_last_fps__;
uint64_t __total_frames__;
bool __keyboard_is_pressed__[GLFW_KEY_LAST + 1];

uint32_t __default_font__[128 * 3] = {
    0,          0,          0,          2177072640, 2579333541, 32451,      4294934016, 3888381915,
    32511,      1998716928, 1048543103, 2076,       1042024448, 473857919,  8,          1010571264,
    417851391,  32280,      2117867520, 410976255,  32280,      0,          1014922812, 0,
    4294967295, 3280044483, 4294967295, 2117861376, 1715618406, 15486,      2177105919, 2579348889,
    4294951809, 1550875648, 858988366,  7731,       1717976064, 2115517542, 6168,       2560161792,
    504895736,  3615,       4274454016, 3871786694, 223207,     3675783168, 2129127294, 6363,
    117637376,  119504671,  259,        1885356032, 1887207292, 16480,      2117867520, 2115508248,
    6204,       1717986816, 26214,      26214,      3688627712, 3638091483, 55512,      214334976,
    1013343804, 8282928,    0,          2130706432, 32639,      2117867520, 2115508248, 8263740,
    2117867520, 404232216,  6168,       404232192,  2115508248, 6204,       402653184,  405831472,
    0,          201326592,  201752326,  0,          0,          2130903811, 0,          603979776,
    610729830,  0,          134742016,  1044257820, 32639,      2139029504, 471612990,  2056,
    0,          0,          0,          505285632,  789534,     3084,       1717986816, 36,
    0,          2134259200, 2134259254, 13878,      54397964,   808459779,  789535,     587202560,
    101455923,  12595,      454757888,  863723278,  28219,      202116096,  6,          0,
    202911744,  201721350,  12312,      403441152,  405811248,  1548,       1711276032, 1715273532,
    0,          402653184,  404258328,  0,          0,          0,          400412,     0,
    32512,      0,          0,          0,          7196,       1614807040, 101455920,  259,
    1935883776, 1735355259, 15971,      252446720,  202116108,  16140,      858988032,  101455920,
    16179,      808656384,  808459312,  7731,       1010315264, 813642550,  30768,      50544384,
    808460035,  7731,       50732032,   858988291,  7731,       1667464960, 202911840,  3084,
    858988032,  859512375,  7731,       858988032,  404241971,  3596,       469762048,  469762076,
    28,         469762048,  469762076,  792604,     202911744,  201720582,  12312,      0,
    8257662,    0,          403441152,  405823536,  1548,       808656384,  789528,     3084,
    1667448320, 58424187,   15875,      857607168,  859779891,  13107,      1717976832, 1717976678,
    16230,      1667644416, 1661141763, 15462,      1714822912, 1717986918, 7990,       105283328,
    103169574,  32582,      1181122304, 103169574,  3846,       1667644416, 1668481795, 31846,
    858993408,  858996531,  13107,      202120704,  202116108,  7692,       808482816,  858992688,
    7731,       912680704,  909516342,  26470,      101060352,  1715865094, 32614,      2138530560,
    1667459967, 25443,      1734566656, 1937473391, 25443,      1664490496, 1667457891, 7222,
    1717976832, 101072486,  3846,       1664490496, 2071159651, 7876670,    1717976832, 1714830950,
    26470,      858988032,  857214467,  7731,       204291840,  202116108,  7692,       858993408,
    858993459,  7731,       858993408,  858993459,  3102,       1667457792, 913009507,  13878,
    858993408,  857607198,  13107,      858993408,  202120755,  7692,       426999552,  1174801432,
    32611,      202128384,  202116108,  15372,      50397184,   806882310,  16480,      808467456,
    808464432,  15408,      1664490504, 0,          0,          0,          0,          16711680,
    1575948,    0,          0,          0,          859713566,  28211,      101058304,  1717986878,
    15206,      0,          50541342,   7731,       808466432,  858993470,  28211,      0,
    54473502,   7731,       104209408,  101064454,  3846,       0,          858993518,  506671166,
    101058304,  1717988918, 26470,      1579008,    404232222,  32280,      3158016,    808464444,
    506671920,  101058304,  907949670,  26470,      404233728,  404232216,  32280,      0,
    1802201919, 25451,      0,          858993439,  13107,      0,          858993438,  7731,
    0,          1717986875, 252067430,  0,          858993518,  2016427571, 0,          107902519,
    3846,       0,          403059486,  7731,       100925440,  101058111,  7222,       0,
    858993459,  28211,      0,          858993459,  3102,       0,          1802199907, 13878,
    0,          471610979,  25398,      0,          1717986918, 253243452,  0,          102248767,
    16163,      202127360,  201720582,  14348,      404232192,  404226072,  6168,       202114816,
    202911768,  1804,       1935396352, 0,          0,          134217728,  1667446300, 127};

static void reshape_callback(GLFWwindow* window, int32_t ww, int32_t wh) {
    int cw, ch;
    glfwGetFramebufferSize(window, &cw, &ch);
    glViewport(0, 0, cw, ch);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ar = (double)(cw) / ch;
    const double oar = (double)(__screen_width__) / __screen_height__;
    ar /= oar;
    if (ar >= 1.0)
        glOrtho(-ar, ar, -1, 1, 1, -1);
    else
        glOrtho(-1, 1, -1 / ar, 1 / ar, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

static void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (action == GLFW_PRESS)
        __keyboard_is_pressed__[key] = true;
    else if (action == GLFW_RELEASE)
        __keyboard_is_pressed__[key] = false;
}

bool is_pressed(int key) { return __keyboard_is_pressed__[key]; }

void cleardevice(color c) { std::fill(__screen_buffer__.begin(), __screen_buffer__.end(), c); }

void set_title(const std::string& title) {
    __window_title__ = title;
    glfwSetWindowTitle(__window_handle__, __window_title__.c_str());
}

const std::string& get_title() { return __window_title__; }

void show_fps() { __show_fps__ = true; }

void hide_fps() {
    __show_fps__ = false;
    glfwSetWindowTitle(__window_handle__, __window_title__.c_str());
}

void initgraph(int width, int height, float multiplier, RenderType rt, int swap_interval) {
    __screen_width__ = width;
    __screen_height__ = height;
    __screen_buffer__.resize(__screen_width__ * __screen_height__);
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    if (multiplier <= 0) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        __window_handle__ =
            glfwCreateWindow(mode->width, mode->height, __window_title__.c_str(), NULL, NULL);
    } else {
        int window_width = __screen_width__ * multiplier;
        int window_height = __screen_height__ * multiplier;
        __window_handle__ =
            glfwCreateWindow(window_width, window_height, __window_title__.c_str(), NULL, NULL);
    }
    if (!__window_handle__) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowAspectRatio(__window_handle__, __screen_width__, __screen_height__);
    glfwSetKeyCallback(__window_handle__, key_callback);
    glfwSetWindowSizeCallback(__window_handle__, reshape_callback);
    glfwMakeContextCurrent(__window_handle__);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);

    glfwSwapInterval(swap_interval);

    glGenTextures(1, &__screen_texture_id__);
    glBindTexture(GL_TEXTURE_2D, __screen_texture_id__);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, __screen_width__, __screen_height__, 0, GL_RGBA,
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

    __last_time__ = glfwGetTime();
    __last_fps__ = -1;
    __frames_till_last_fps__ = 0;
    __total_frames__ = 0;
}

void closegraph() {
    glfwDestroyWindow(__window_handle__);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void putpixel(int x, int y, color c) { __screen_buffer__[y * __screen_width__ + x] = c; }
color& getpixel(int x, int y) { return __screen_buffer__[y * __screen_width__ + x]; }

void outtextxy(int x, int y, const std::string& text) {
    if (y <= -12 || y >= __screen_height__)
        return;
    const int tl = 8 * text.length();
    if (x <= -tl || x >= __screen_width__)
        return;
    const int sy = std::max(y, 0), ey = std::min(y + 12, __screen_height__);
    unsigned char* font = (unsigned char*)__default_font__;
    int st = std::max(0, -x / 8);
    if (x < 0) {
        x %= 8;
        if (x != 0) {
            char c = text[st];
            for (int j = sy; j < ey; j++)
                for (int i = 0, v = font[c * 12 + j - y] >> -x; i < 8 + x; i++, v /= 2)
                    if (v & 1)
                        putpixel(i, j, 0xffffff);
            x += 8; // 12x30
            st++;
        }
    }
    int et = std::min(__screen_width__ - x, tl) / 8;
    for (; st < et; st++, x += 8) {
        char c = text[st];
        for (int j = sy; j < ey; j++)
            for (int i = 0, v = font[c * 12 + j - y]; i < 8; i++, v /= 2)
                if (v & 1)
                    putpixel(x + i, j, 0xffffff);
    }
    if (st < tl) {
        const int ex = __screen_width__ - x;
        char c = text[st];
        for (int j = sy; j < ey; j++)
            for (int i = 0, v = font[c * 12 + j - y]; i < ex; i++, v /= 2)
                if (v & 1)
                    putpixel(x + i, j, 0xffffff);
    }
}

bool not_closed() { return !glfwWindowShouldClose(__window_handle__); }

void bitblt() {
    // glClear(GL_COLOR_BUFFER_BIT);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, __screen_width__, __screen_height__, GL_RGBA,
                    GL_UNSIGNED_BYTE, __screen_buffer__.data());
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
    glfwPollEvents();

    if (__show_fps__) {
        __frames_till_last_fps__++;
        double curTime = glfwGetTime();
        double delta = curTime - __last_time__;
        if (delta >= 1.0) {
            double fps = __frames_till_last_fps__ / delta;
            // if (__last_fps__ > 0)
            //     fps = 0.3 * fps + 0.7 * __last_fps__;
            std::string title = __window_title__ + " fps: " + std::to_string(fps);
            glfwSetWindowTitle(__window_handle__, title.c_str());
            __frames_till_last_fps__ = 0;
            __last_time__ = curTime;
            __last_fps__ = fps;
        }
    }
    __total_frames__++;
}

} // namespace lfbg