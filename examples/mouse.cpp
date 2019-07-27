#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

// #include <glad/glad.h>
// //#define GLFW_INCLUDE_NONE
// //#include "linmath.h"
// #include <GLFW/glfw3.h>
// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <utility>
// #include <tuple>
// #include <chrono>
// #include <thread>
// #include <functional>

// typedef uint32_t color;

// namespace COLOR {
// const color BLACK = 0x000000;
// const color BLUE = 0x0000AA;
// const color GREEN = 0x00AA00;
// const color CYAN = 0x00AAAA;
// const color RED = 0xAA0000;
// const color MAGENTA = 0xAA00AA;
// const color BROWN = 0xAA5500;
// const color GRAY = 0xAAAAAA;
// const color DARK_GRAY = 0x555555;
// const color BRIGHT_BLUE = 0x5555FF;
// const color BRIGHT_GREEN = 0x55FF55;
// const color BRIGHT_CYAN = 0x55FFFF;
// const color BRIGHT_RED = 0xFF5555;
// const color BRIGHT_MAGENTA = 0xFF55FF;
// const color YELLOW = 0xFFFF55;
// const color WHITE = 0xFFFFFF;

// color fromRGB(int r, int g, int b) { return ((b & 255) << 16) | ((g & 255) << 8) | (r & 255); }

// } // namespace COLOR

// uint32_t __default_font__[128 * 3] = {
//     0,          0,          0,          2177072640, 2579333541, 32451,      4294934016,
//     3888381915, 32511,      1998716928, 1048543103, 2076,       1042024448, 473857919,  8,
//     1010571264, 417851391,  32280,      2117867520, 410976255,  32280,      0, 1014922812, 0,
//     4294967295, 3280044483, 4294967295, 2117861376, 1715618406, 15486,      2177105919,
//     2579348889, 4294951809, 1550875648, 858988366,  7731,       1717976064, 2115517542, 6168,
//     2560161792, 504895736,  3615,       4274454016, 3871786694, 223207,     3675783168,
//     2129127294, 6363, 117637376,  119504671,  259,        1885356032, 1887207292, 16480,
//     2117867520, 2115508248, 6204,       1717986816, 26214,      26214,      3688627712,
//     3638091483, 55512,      214334976, 1013343804, 8282928,    0,          2130706432, 32639,
//     2117867520, 2115508248, 8263740, 2117867520, 404232216,  6168,       404232192,  2115508248,
//     6204,       402653184,  405831472, 0,          201326592,  201752326,  0,          0,
//     2130903811, 0,          603979776, 610729830,  0,          134742016,  1044257820, 32639,
//     2139029504, 471612990,  2056, 0,          0,          0,          505285632,  789534, 3084,
//     1717986816, 36, 0,          2134259200, 2134259254, 13878,      54397964,   808459779,
//     789535,     587202560, 101455923,  12595,      454757888,  863723278,  28219,      202116096,
//     6,          0, 202911744,  201721350,  12312,      403441152,  405811248,  1548, 1711276032,
//     1715273532, 0,          402653184,  404258328,  0,          0,          0,          400412,
//     0, 32512,      0,          0,          0,          7196,       1614807040, 101455920,  259,
//     1935883776, 1735355259, 15971,      252446720,  202116108,  16140,      858988032, 101455920,
//     16179,      808656384,  808459312,  7731,       1010315264, 813642550,  30768,      50544384,
//     808460035,  7731,       50732032,   858988291,  7731,       1667464960, 202911840,  3084,
//     858988032,  859512375,  7731,       858988032,  404241971,  3596,       469762048, 469762076,
//     28,         469762048,  469762076,  792604,     202911744,  201720582,  12312,      0,
//     8257662,    0,          403441152,  405823536,  1548,       808656384,  789528,     3084,
//     1667448320, 58424187,   15875,      857607168,  859779891,  13107,      1717976832,
//     1717976678, 16230,      1667644416, 1661141763, 15462,      1714822912, 1717986918, 7990,
//     105283328, 103169574,  32582,      1181122304, 103169574,  3846,       1667644416,
//     1668481795, 31846, 858993408,  858996531,  13107,      202120704,  202116108,  7692,
//     808482816,  858992688, 7731,       912680704,  909516342,  26470,      101060352, 1715865094,
//     32614,      2138530560, 1667459967, 25443,      1734566656, 1937473391, 25443, 1664490496,
//     1667457891, 7222, 1717976832, 101072486,  3846,       1664490496, 2071159651, 7876670,
//     1717976832, 1714830950, 26470,      858988032,  857214467,  7731,       204291840, 202116108,
//     7692,       858993408, 858993459,  7731,       858993408,  858993459,  3102, 1667457792,
//     913009507,  13878, 858993408,  857607198,  13107,      858993408,  202120755,  7692,
//     426999552,  1174801432, 32611,      202128384,  202116108,  15372,      50397184, 806882310,
//     16480,      808467456, 808464432,  15408,      1664490504, 0,          0,          0, 0,
//     16711680, 1575948,    0,          0,          0,          859713566,  28211,      101058304,
//     1717986878, 15206,      0,          50541342,   7731,       808466432,  858993470,  28211, 0,
//     54473502,   7731,       104209408,  101064454,  3846,       0,          858993518, 506671166,
//     101058304,  1717988918, 26470,      1579008,    404232222,  32280,      3158016, 808464444,
//     506671920,  101058304,  907949670,  26470,      404233728,  404232216,  32280,      0,
//     1802201919, 25451,      0,          858993439,  13107,      0,          858993438,  7731,
//     0,          1717986875, 252067430,  0,          858993518,  2016427571, 0, 107902519, 3846,
//     0,          403059486,  7731,       100925440,  101058111,  7222,       0, 858993459,  28211,
//     0,          858993459,  3102,       0,          1802199907, 13878, 0,          471610979,
//     25398,      0,          1717986918, 253243452,  0,          102248767, 16163,      202127360,
//     201720582,  14348,      404232192,  404226072,  6168,       202114816, 202911768,  1804,
//     1935396352, 0,          0,          134217728,  1667446300, 127};

// class window {
//     GLuint _texture_id;
//     GLFWwindow* _window_handle;
//     int _width, _height;
//     std::vector<color> _buffer;
//     color _foreground_color = 0xffffff;
//     std::string _title;
//     bool _show_fps = true;
//     double _last_time, _last_fps;
//     int _frames_till_last_fps;
//     uint64_t _total_frames;
//     bool _keyboard_is_pressed[GLFW_KEY_LAST + 1];
//     bool _keyboard_is_up[GLFW_KEY_LAST + 1];
//     bool _keyboard_is_down[GLFW_KEY_LAST + 1];
//     int _kbhit = 0;
//     std::function<void(int, int)> _window_resize_callback;
//     std::function<void(int, int, int, int)> _keyboard_callback;
//     std::function<void(double, double)> _cursor_pos_callback;
//     std::function<void(int, int, int)> _mouse_button_callback;
//     double _cursor_x, _cursor_y;
//     int _window_width, _window_height;
//     bool _mouse_is_pressed[GLFW_MOUSE_BUTTON_LAST + 1];
//     bool _mouse_is_up[GLFW_MOUSE_BUTTON_LAST + 1];
//     bool _mouse_is_down[GLFW_MOUSE_BUTTON_LAST + 1];

// public:
//     window() : _window_handle(nullptr) {}

//     ~window() {
//         if (_window_handle != nullptr)
//             close();
//     }

//     void close() {
//         if (_window_handle != nullptr) {
//             glfwDestroyWindow(_window_handle);
//             glfwTerminate();
//             _window_handle = nullptr;
//         }
//     }

//     std::pair<int, int> get_buffer_size() const { return {_width, _height}; }

//     std::pair<int, int> get_window_size() const { return {_window_width, _window_height}; }

//     std::pair<double, double> get_cursor_pos() const {
//         return {_cursor_x * _width / _window_width, _cursor_y * _height / _window_height};
//     }

//     void set_keyboard_callback(std::function<void(int, int, int, int)> callback_function) {
//         _keyboard_callback = callback_function;
//     }

//     void set_cursor_pos_callback(std::function<void(double, double)> callback_function) {
//         _cursor_pos_callback = callback_function;
//     }

//     void set_mouse_button_callback(std::function<void(int, int, int)> callback_function) {
//         _mouse_button_callback = callback_function;
//     }

//     void set_default_resize_callback() {
//         _window_resize_callback = [&](int32_t, int32_t) {
//             glfwGetFramebufferSize(_window_handle, &_window_width, &_window_height);
//             glViewport(0, 0, _window_width, _window_height);
//             glMatrixMode(GL_PROJECTION);
//             glLoadIdentity();
//             double ar = (double)(_window_width) / _window_height;
//             const double oar = (double)(_width) / _height;
//             ar /= oar;
//             if (ar >= 1.0)
//                 glOrtho(-ar, ar, -1, 1, 1, -1);
//             else
//                 glOrtho(-1, 1, -1 / ar, 1 / ar, 1.0, -1.0);

//             glMatrixMode(GL_MODELVIEW);
//             glLoadIdentity();
//             glClear(GL_COLOR_BUFFER_BIT);
//         };
//     }

//     void set_default_keyboard_callback() {
//         _keyboard_callback = [&](int key, int, int action, int) {
//             if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//                 glfwSetWindowShouldClose(_window_handle, GLFW_TRUE);
//             if (action == GLFW_PRESS) {
//                 _keyboard_is_pressed[key] = true;
//                 _keyboard_is_down[key] = true;
//             } else if (action == GLFW_RELEASE) {
//                 _keyboard_is_pressed[key] = false;
//                 _keyboard_is_up[key] = true;
//                 _kbhit = key;
//             }
//         };
//     }

//     void set_default_cursor_pos_callback() {
//         _cursor_pos_callback = [&](double xpos, double ypos) {
//             _cursor_x = xpos;
//             _cursor_y = ypos;
//         };
//     }

//     void set_default_mouse_button_callback() {
//         _mouse_button_callback = [&](int button, int action, int) {
//             if (action == GLFW_PRESS) {
//                 _mouse_is_pressed[button] = true;
//                 _mouse_is_down[button] = true;
//             } else if (action == GLFW_RELEASE) {
//                 _mouse_is_pressed[button] = false;
//                 _mouse_is_up[button] = true;
//             }
//         };
//     }

//     void init(int width, int height, float multiplier, int swap_interval) {
//         _width = width;
//         _height = height;
//         _buffer.resize(_width * _height);
//         glfwSetErrorCallback([](int error, const char* description) {
//             std::cerr << "Error (" << error << "): " << description << std::endl;
//         });
//         if (!glfwInit())
//             exit(EXIT_FAILURE);
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//         if (multiplier < 0) {
//             GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//             const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//             _window_width = mode->width;
//             _window_height = mode->height;
//             _window_handle = glfwCreateWindow(_window_width, _window_height, _title.c_str(),
//                                               glfwGetPrimaryMonitor(), NULL);
//         } else if (multiplier == 0) {
//             GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//             const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//             _window_width = mode->width;
//             _window_height = mode->height;
//             _window_handle =
//                 glfwCreateWindow(_window_width, _window_height, _title.c_str(), NULL, NULL);
//             glfwMaximizeWindow(_window_handle);
//         } else {
//             _window_width = _width * multiplier;
//             _window_height = _height * multiplier;
//             _window_handle =
//                 glfwCreateWindow(_window_width, _window_height, _title.c_str(), NULL, NULL);
//         }
//         if (!_window_handle) {
//             glfwTerminate();
//             exit(EXIT_FAILURE);
//         }
//         set_default_resize_callback();
//         glfwSetWindowSizeCallback(_window_handle, [](GLFWwindow* handle, int32_t w, int32_t h) {
//             window* obj = (window*)glfwGetWindowUserPointer(handle);
//             obj->_window_resize_callback(w, h);
//         });

//         glfwSetWindowUserPointer(_window_handle, this);
//         glfwSetWindowAspectRatio(_window_handle, _width, _height);

//         set_default_keyboard_callback();
//         glfwSetKeyCallback(_window_handle, [](GLFWwindow* handle, int k, int s, int a, int m) {
//             window* obj = (window*)glfwGetWindowUserPointer(handle);
//             obj->_keyboard_callback(k, s, a, m);
//         });

//         set_default_cursor_pos_callback();
//         glfwSetCursorPosCallback(_window_handle, [](GLFWwindow* handle, double x, double y) {
//             window* obj = (window*)glfwGetWindowUserPointer(handle);
//             obj->_cursor_pos_callback(x, y);
//         });

//         set_default_cursor_pos_callback();
//         glfwSetCursorPosCallback(_window_handle, [](GLFWwindow* handle, double x, double y) {
//             window* obj = (window*)glfwGetWindowUserPointer(handle);
//             obj->_cursor_pos_callback(x, y);
//         });

//         glfwMakeContextCurrent(_window_handle);
//         gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

//         glEnable(GL_TEXTURE_2D);
//         glDisable(GL_BLEND);
//         glDisable(GL_DEPTH_TEST);
//         glDisable(GL_SCISSOR_TEST);

//         glfwSwapInterval(swap_interval);

//         glGenTextures(1, &_texture_id);
//         glBindTexture(GL_TEXTURE_2D, _texture_id);
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE,
//                      _buffer.data());
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//         glActiveTexture(GL_TEXTURE0);

//         _last_time = glfwGetTime();
//         _last_fps = -1;
//         _frames_till_last_fps = 0;
//         _total_frames = 0;
//     }

//     bool is_closed() { return glfwWindowShouldClose(_window_handle); }

//     void bitblt() {
//         glClear(GL_COLOR_BUFFER_BIT);
//         glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_BGRA, GL_UNSIGNED_BYTE,
//                         _buffer.data());
//         glBegin(GL_TRIANGLE_FAN);
//         glTexCoord2f(0, 0);
//         glVertex2f(-1, 1);
//         glTexCoord2f(1, 0);
//         glVertex2f(1, 1);
//         glTexCoord2f(1, 1);
//         glVertex2f(1, -1);
//         glTexCoord2f(0, 1);
//         glVertex2f(-1, -1);
//         glEnd();
//         glfwSwapBuffers(_window_handle);
//         _kbhit = 0;
//         for (size_t i = 0; i < GLFW_KEY_LAST + 1; i++)
//             _keyboard_is_down[i] = _keyboard_is_up[i] = false;
//         glfwPollEvents();

//         if (_show_fps) {
//             _frames_till_last_fps++;
//             double curTime = glfwGetTime();
//             double delta = curTime - _last_time;
//             if (delta >= 1.0) {
//                 double fps = _frames_till_last_fps / delta;
//                 // if (__last_fps__ > 0)
//                 //     fps = 0.3 * fps + 0.7 * __last_fps__;
//                 std::string title = _title + " fps: " + std::to_string(fps);
//                 glfwSetWindowTitle(_window_handle, title.c_str());
//                 _frames_till_last_fps = 0;
//                 _last_time = curTime;
//                 _last_fps = fps;
//             }
//         }
//         _total_frames++;
//     }

//     void retro(bool use_retro) {
//         if (use_retro) {
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//         } else {
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         }
//     }

//     void clear(color c) { std::fill(_buffer.begin(), _buffer.end(), c); }

//     void setcolor(color c) { _foreground_color = c; }

//     color getcolor() { return _foreground_color; }

//     void putpixel(int x, int y, color c) {
//         if (0 <= x && x < _width && 0 <= y && y < _height)
//             _buffer[y * _width + x] = c;
//     }

//     color getpixel(int x, int y) {
//         if (0 <= x && x < _width && 0 <= y && y < _height)
//             return _buffer[y * _width + x];
//         return -1;
//     }

//     void outtextxy(int x, int y, const std::string& text) {
//         if (y <= -12 || y >= _height)
//             return;
//         const int tl = 8 * text.length();
//         if (x <= -tl || x >= _width)
//             return;
//         const int sy = std::max(y, 0), ey = std::min(y + 12, _height);
//         unsigned char* font = (unsigned char*)__default_font__;
//         int st = std::max(0, -x / 8);
//         if (x < 0) {
//             x %= 8;
//             if (x != 0) {
//                 char c = text[st];
//                 for (int j = sy; j < ey; j++)
//                     for (int i = 0, v = font[c * 12 + j - y] >> -x; i < 8 + x; i++, v /= 2)
//                         if (v & 1)
//                             putpixel(i, j, _foreground_color);
//                 x += 8; // 12x30
//                 st++;
//             }
//         }
//         int et = std::min(_width - x, tl) / 8;
//         for (; st < et; st++, x += 8) {
//             char c = text[st];
//             for (int j = sy; j < ey; j++)
//                 for (int i = 0, v = font[c * 12 + j - y]; i < 8; i++, v /= 2)
//                     if (v & 1)
//                         putpixel(i + x, j, _foreground_color);
//         }
//         if (st < tl) {
//             const int ex = _width - x;
//             char c = text[st];
//             for (int j = sy; j < ey; j++)
//                 for (int i = 0, v = font[c * 12 + j - y]; i < ex; i++, v /= 2)
//                     if (v & 1)
//                         putpixel(i + x, j, _foreground_color);
//         }
//     }
// };

int main(int argc, char* argv[]) {
    using namespace std;

    // window w;
    // float multiplier = 1;
    // if (argc > 1)
    //     multiplier = std::stof(argv[1]);
    // w.init(320, 240, multiplier, 1);
    // while (!w.is_closed()) {
    //     w.clear(COLOR::CYAN);
    //     auto [wx, wy] = w.get_window_size();
    //     w.outtextxy(20, 50, "window: " + to_string(wx) + "x" + to_string(wy));
    //     auto [mx, my] = w.get_cursor_pos();
    //     w.outtextxy(20, 100, "Mouse: " + to_string(mx) + "x" + to_string(my));
    //     w.bitblt();
    // }
    // w.close();

    using namespace lfbg;

    constexpr int width = 320, height = 200;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro, 1);

    while (!closed()) {
        cleardevice(COLOR::CYAN);
        putpixel(0, 0, COLOR::WHITE);
        putpixel(width - 1, 0, COLOR::WHITE);
        putpixel(width - 1, height - 1, COLOR::WHITE);
        putpixel(0, height - 1, COLOR::WHITE);
        auto [wx, wy] = get_window_size();
        outtextxy(20, 50, "window: " + to_string(wx) + "x" + to_string(wy));
        auto [mx, my] = get_cursor_pos();
        outtextxy(20, 100, "Mouse: " + to_string(mx) + "x" + to_string(my));
        bitblt();
    }
    closegraph();
}
