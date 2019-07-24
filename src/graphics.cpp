#include "lfbg/graphics.h"

namespace lfbg {

namespace COLOR {
const color BLACK = 0x000000;
const color BLUE = 0x0000AA;
const color GREEN = 0x00AA00;
const color CYAN = 0x00AAAA;
const color RED = 0xAA0000;
const color MAGENTA = 0xAA00AA;
const color BROWN = 0xAA5500;
const color GRAY = 0xAAAAAA;
const color DARK_GRAY = 0x555555;
const color BRIGHT_BLUE = 0x5555FF;
const color BRIGHT_GREEN = 0x55FF55;
const color BRIGHT_CYAN = 0x55FFFF;
const color BRIGHT_RED = 0xFF5555;
const color BRIGHT_MAGENTA = 0xFF55FF;
const color YELLOW = 0xFFFF55;
const color WHITE = 0xFFFFFF;
} // namespace COLOR

GLuint __screen_texture_id__;
GLFWwindow* __window_handle__;
int __screen_width__, __screen_height__;
std::vector<color> __screen_buffer__;
color __foreground_color__ = COLOR::WHITE;
std::string __window_title__;
bool __show_fps__ = true;
double __last_time__, __last_fps__;
int __frames_till_last_fps__;
uint64_t __total_frames__;
bool __keyboard_is_pressed__[GLFW_KEY_LAST + 1];
bool __keyboard_is_up__[GLFW_KEY_LAST + 1];
bool __keyboard_is_down__[GLFW_KEY_LAST + 1];
int __kbhit__ = 0;

color palette[256] = { // Default VGA Palette
    0x000000, 0x800000, 0x008000, 0x808000, 0x000080, 0x800080, 0x008080, 0xc0c0c0, 0x808080,
    0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff, 0x00ffff, 0xffffff, 0x000000, 0x00005f,
    0x000087, 0x0000af, 0x0000d7, 0x0000ff, 0x005f00, 0x005f5f, 0x005f87, 0x005faf, 0x005fd7,
    0x005fff, 0x008700, 0x00875f, 0x008787, 0x0087af, 0x0087d7, 0x0087ff, 0x00af00, 0x00af5f,
    0x00af87, 0x00afaf, 0x00afd7, 0x00afff, 0x00d700, 0x00d75f, 0x00d787, 0x00d7af, 0x00d7d7,
    0x00d7ff, 0x00ff00, 0x00ff5f, 0x00ff87, 0x00ffaf, 0x00ffd7, 0x00ffff, 0x5f0000, 0x5f005f,
    0x5f0087, 0x5f00af, 0x5f00d7, 0x5f00ff, 0x5f5f00, 0x5f5f5f, 0x5f5f87, 0x5f5faf, 0x5f5fd7,
    0x5f5fff, 0x5f8700, 0x5f875f, 0x5f8787, 0x5f87af, 0x5f87d7, 0x5f87ff, 0x5faf00, 0x5faf5f,
    0x5faf87, 0x5fafaf, 0x5fafd7, 0x5fafff, 0x5fd700, 0x5fd75f, 0x5fd787, 0x5fd7af, 0x5fd7d7,
    0x5fd7ff, 0x5fff00, 0x5fff5f, 0x5fff87, 0x5fffaf, 0x5fffd7, 0x5fffff, 0x870000, 0x87005f,
    0x870087, 0x8700af, 0x8700d7, 0x8700ff, 0x875f00, 0x875f5f, 0x875f87, 0x875faf, 0x875fd7,
    0x875fff, 0x878700, 0x87875f, 0x878787, 0x8787af, 0x8787d7, 0x8787ff, 0x87af00, 0x87af5f,
    0x87af87, 0x87afaf, 0x87afd7, 0x87afff, 0x87d700, 0x87d75f, 0x87d787, 0x87d7af, 0x87d7d7,
    0x87d7ff, 0x87ff00, 0x87ff5f, 0x87ff87, 0x87ffaf, 0x87ffd7, 0x87ffff, 0xaf0000, 0xaf005f,
    0xaf0087, 0xaf00af, 0xaf00d7, 0xaf00ff, 0xaf5f00, 0xaf5f5f, 0xaf5f87, 0xaf5faf, 0xaf5fd7,
    0xaf5fff, 0xaf8700, 0xaf875f, 0xaf8787, 0xaf87af, 0xaf87d7, 0xaf87ff, 0xafaf00, 0xafaf5f,
    0xafaf87, 0xafafaf, 0xafafd7, 0xafafff, 0xafd700, 0xafd75f, 0xafd787, 0xafd7af, 0xafd7d7,
    0xafd7ff, 0xafff00, 0xafff5f, 0xafff87, 0xafffaf, 0xafffd7, 0xafffff, 0xd70000, 0xd7005f,
    0xd70087, 0xd700af, 0xd700d7, 0xd700ff, 0xd75f00, 0xd75f5f, 0xd75f87, 0xd75faf, 0xd75fd7,
    0xd75fff, 0xd78700, 0xd7875f, 0xd78787, 0xd787af, 0xd787d7, 0xd787ff, 0xd7af00, 0xd7af5f,
    0xd7af87, 0xd7afaf, 0xd7afd7, 0xd7afff, 0xd7d700, 0xd7d75f, 0xd7d787, 0xd7d7af, 0xd7d7d7,
    0xd7d7ff, 0xd7ff00, 0xd7ff5f, 0xd7ff87, 0xd7ffaf, 0xd7ffd7, 0xd7ffff, 0xff0000, 0xff005f,
    0xff0087, 0xff00af, 0xff00d7, 0xff00ff, 0xff5f00, 0xff5f5f, 0xff5f87, 0xff5faf, 0xff5fd7,
    0xff5fff, 0xff8700, 0xff875f, 0xff8787, 0xff87af, 0xff87d7, 0xff87ff, 0xffaf00, 0xffaf5f,
    0xffaf87, 0xffafaf, 0xffafd7, 0xffafff, 0xffd700, 0xffd75f, 0xffd787, 0xffd7af, 0xffd7d7,
    0xffd7ff, 0xffff00, 0xffff5f, 0xffff87, 0xffffaf, 0xffffd7, 0xffffff, 0x080808, 0x121212,
    0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a, 0x444444, 0x4e4e4e, 0x585858, 0x626262, 0x6c6c6c,
    0x767676, 0x808080, 0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6,
    0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee};

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
    std::cerr << "Error (" << error << "): " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (action == GLFW_PRESS) {
        __keyboard_is_pressed__[key] = true;
        __keyboard_is_down__[key] = true;
    } else if (action == GLFW_RELEASE) {
        __keyboard_is_pressed__[key] = false;
        __keyboard_is_up__[key] = true;
        __kbhit__ = key;
    }
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

void cleardevice(color c) { std::fill(__screen_buffer__.begin(), __screen_buffer__.end(), c); }

void setcolor(color c) { __foreground_color__ = c; }

color getcolor() { return __foreground_color__; }

void putpixel(int x, int y, color c) {
    if (0 <= x && x <= __screen_width__ && 0 <= y && y <= __screen_height__)
        __screen_buffer__[y * __screen_width__ + x] = c;
}

color getpixel(int x, int y) {
    if (0 <= x && x <= __screen_width__ && 0 <= y && y <= __screen_height__)
        return __screen_buffer__[y * __screen_width__ + x];
    return -1;
}

constexpr int COHEN_SUTHERLAND_INSIDE = 0b0000;
constexpr int COHEN_SUTHERLAND_LEFT = 0b0001;
constexpr int COHEN_SUTHERLAND_RIGHT = 0b0010;
constexpr int COHEN_SUTHERLAND_BOTTOM = 0b0100;
constexpr int COHEN_SUTHERLAND_TOP = 0b1000;

int cohen_sutherland_code(int x, int y) {
    int code = COHEN_SUTHERLAND_INSIDE;
    if (x < 0)
        code |= COHEN_SUTHERLAND_LEFT;
    else if (x >= __screen_width__)
        code |= COHEN_SUTHERLAND_RIGHT;
    if (y < 0)
        code |= COHEN_SUTHERLAND_BOTTOM;
    else if (y >= __screen_height__)
        code |= COHEN_SUTHERLAND_TOP;
    return code;
}

bool cohen_sutherland_clip(int& x1, int& y1, int& x2, int& y2) {
    int c1 = cohen_sutherland_code(x1, y1);
    int c2 = cohen_sutherland_code(x2, y2);
    bool accept = false;
    while (true) {
        if (c1 == 0 && c2 == 0) { // If both endpoints lie within rectangle
            accept = true;
            break;
        } else if (c1 & c2) { // If both endpoints are outside rectangle, in same region
            break;
        } else { // Some segment of line lies within the rectangle
            double x, y;
            // At least one endpoint is outside the
            // rectangle, pick it.
            int co = c1 != 0 ? c1 : c2;
            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (co & COHEN_SUTHERLAND_TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (__screen_height__ - 1 - y1) / (y2 - y1);
                y = __screen_height__ - 1;
            } else if (co & COHEN_SUTHERLAND_BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (0 - y1) / (y2 - y1);
                y = 0;
            } else if (co & COHEN_SUTHERLAND_RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (__screen_width__ - 1 - x1) / (x2 - x1);
                x = __screen_width__ - 1;
            } else if (co & COHEN_SUTHERLAND_LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (0 - x1) / (x2 - x1);
                x = 0;
            }
            // Now intersection point x,y is found. We replace point outside rectangle by
            // intersection point
            if (co == c1) {
                x1 = x;
                y1 = y;
                c1 = cohen_sutherland_code(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                c2 = cohen_sutherland_code(x2, y2);
            }
        }
    }
    return accept;
}

void line(int x1, int y1, int x2, int y2) {
    if (!cohen_sutherland_clip(x1, y1, x2, y2))
        return;
    int x, y, dx, dy, incx, incy, balance;

    if (x2 >= x1) {
        dx = x2 - x1;
        incx = 1;
    } else {
        dx = x1 - x2;
        incx = -1;
    }

    if (y2 >= y1) {
        dy = y2 - y1;
        incy = 1;
    } else {
        dy = y1 - y2;
        incy = -1;
    }

    x = x1;
    y = y1;

    if (dx >= dy) {
        dy <<= 1;
        balance = dy - dx;
        dx <<= 1;

        while (x != x2) {
            __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
            if (balance >= 0) {
                y += incy;
                balance -= dx;
            }
            balance += dy;
            x += incx;
        }
        __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
    } else {
        dx <<= 1;
        balance = dx - dy;
        dy <<= 1;

        while (y != y2) {
            __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
            if (balance >= 0) {
                x += incx;
                balance -= dy;
            }
            balance += dx;
            y += incy;
        }
        __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
    }
}

void bresenham_symmetric_plot(int xc, int yc, int x, int y) {
    putpixel(x + xc, y + yc, __foreground_color__);
    putpixel(x + xc, -y + yc, __foreground_color__);
    putpixel(-x + xc, -y + yc, __foreground_color__);
    putpixel(-x + xc, y + yc, __foreground_color__);
    putpixel(y + xc, x + yc, __foreground_color__);
    putpixel(y + xc, -x + yc, __foreground_color__);
    putpixel(-y + xc, -x + yc, __foreground_color__);
    putpixel(-y + xc, x + yc, __foreground_color__);
}

void circle(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - (2 * r);
    bresenham_symmetric_plot(xc, yc, x, y);
    while (x <= y) {
        if (d <= 0) {
            d = d + (4 * x) + 6;
        } else {
            d = d + (4 * x) - (4 * y) + 10;
            y = y - 1;
        }
        x = x + 1;
        bresenham_symmetric_plot(xc, yc, x, y);
    }
}

void hline(int x1, int x2, int y) {
    if (x1 > x2)
        std::swap(x1, x2);
    if (0 <= y && y < __screen_height__ && x2 > 0 && x1 < __screen_width__) {
        if (x1 < 0)
            x1 = 0;
        if (x2 >= __screen_width__)
            x2 = __screen_width__ - 1;
        for (; x1 <= x2; x1++)
            __screen_buffer__[y * __screen_width__ + x1] = __foreground_color__;
    }
}

void vline(int y1, int y2, int x) {
    if (y1 > y2)
        std::swap(y1, y2);
    if (0 <= x && x < __screen_width__ && y2 > 0 && y1 < __screen_height__) {
        if (y1 < 0)
            y1 = 0;
        if (y2 >= __screen_height__)
            y2 = __screen_height__ - 1;
        for (; y1 <= y2; y1++)
            __screen_buffer__[y1 * __screen_width__ + x] = __foreground_color__;
    }
}

void rectangle(int left, int top, int right, int bottom) {
    hline(left, right, top);
    hline(left, right, bottom);
    vline(top, bottom, left);
    vline(top, bottom, right);
}

void bar(int left, int top, int right, int bottom) {
    if (left > right)
        std::swap(left, right);
    if (top > bottom)
        std::swap(top, bottom);
    if (right < 0 || left >= __screen_width__ || bottom < 0 || top >= __screen_height__)
        return;
    if (left < 0)
        left = 0;
    if (right >= __screen_width__)
        right = __screen_width__ - 1;
    if (top < 0)
        top = 0;
    if (bottom >= __screen_height__)
        bottom = __screen_height__ - 1;
    auto begin = __screen_buffer__.begin() + left;
    auto end = __screen_buffer__.begin() + right + 1;
    for (int offset = top * __screen_width__; top <= bottom; top++, offset += __screen_width__)
        std::fill(begin + offset, end + offset, __foreground_color__);
}

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
                        __screen_buffer__[j * __screen_width__ + i] = __foreground_color__;
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
                    __screen_buffer__[j * __screen_width__ + i + x] = __foreground_color__;
    }
    if (st < tl) {
        const int ex = __screen_width__ - x;
        char c = text[st];
        for (int j = sy; j < ey; j++)
            for (int i = 0, v = font[c * 12 + j - y]; i < ex; i++, v /= 2)
                if (v & 1)
                    __screen_buffer__[j * __screen_width__ + i + x] = __foreground_color__;
    }
}

// extra

bool closed() { return glfwWindowShouldClose(__window_handle__); }

void bitblt() {
    glClear(GL_COLOR_BUFFER_BIT);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, __screen_width__, __screen_height__, GL_BGRA,
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
    __kbhit__ = 0;
    for (size_t i = 0; i < GLFW_KEY_LAST + 1; i++)
        __keyboard_is_down__[i] = __keyboard_is_up__[i] = false;
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

int kbhit() {
    bitblt();
    return __kbhit__;
}

bool is_key_pressed(int key) { return __keyboard_is_pressed__[key]; }

bool is_key_down(int key) { return __keyboard_is_down__[key]; }

bool is_key_up(int key) { return __keyboard_is_up__[key]; }

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

} // namespace lfbg