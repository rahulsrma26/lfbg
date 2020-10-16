#pragma once

#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include "linmath.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <utility>
#include <tuple>
#include <chrono>
#include <thread>
#include <functional>
#include <cmath>
#include <queue>
#include <fstream>
#include <sstream>

namespace lfbg {

typedef uint32_t color;

namespace COLOR {
extern const color BLACK;
extern const color BLUE;
extern const color GREEN;
extern const color CYAN;
extern const color RED;
extern const color MAGENTA;
extern const color BROWN;
extern const color GRAY;
extern const color DARK_GRAY;
extern const color BRIGHT_BLUE;
extern const color BRIGHT_GREEN;
extern const color BRIGHT_CYAN;
extern const color BRIGHT_RED;
extern const color BRIGHT_MAGENTA;
extern const color YELLOW;
extern const color WHITE;
} // namespace COLOR

namespace TEXT {
extern const int LEFT;
extern const int RIGHT;
extern const int TOP;
extern const int BOTTOM;
extern const int CENTER;
} // namespace TEXT


enum class RenderType { Retro, Smooth };

enum class ColorOptimization { None, Threshold, FloydSteinberg, FilterLite, Ordered2x2, Ordered4x4 };

struct Image{
    uint8_t bit_depth;
    int width, height;
    std::vector<uint8_t> palette;
    std::vector<uint8_t> pixels;
    void draw(int x, int y) const;
    static Image fromBMP(const char* fname);
};

struct window_helper {
    std::function<void(int, int)> window_resize_callback;
    std::function<void(int, int, int, int)> keyboard_callback;
    std::function<void(double, double)> cursor_pos_callback;
    std::function<void(int, int, int)> mouse_button_callback;
};

// core
GLFWwindow* initgraph(int width, int height, float multiplier = 1,
                      RenderType rt = RenderType::Retro, int swap_interval = 0);
void closegraph();
void bitblt();
void bitblt(const std::vector<color>&);
GLFWwindow* get_window_handle();

// basic
void cleardevice(color c = COLOR::BLACK);
void putpixel(int x, int y, color);
color getpixel(int x, int y);
void setcolor(color);
color getcolor();
void set_title(const std::string& title);
const std::string& get_title();

// callback
void set_default_window_resize_callback();

// info
bool closed();
std::pair<int, int> get_buffer_size();
std::pair<int, int> get_window_size();

// color
void enable_palette(ColorOptimization co = ColorOptimization::None, int palette_size = 256);
void disable_palette();
bool using_palette();
void set_palette(int idx, color);
color get_palette(int idx);
color rgb2color(uint8_t r, uint8_t g, uint8_t b);
std::tuple<uint8_t, uint8_t, uint8_t> color2rgb(color c);

// drawables
void setfillstyle(int style, color);
void setfillpattern(uint64_t pattern8x8);
uint64_t getfillpattern();
color getfillcolor();
void line(int x1, int y1, int x2, int y2);
void circle(int x, int y, int r);
void arc(int x, int y, int start, int end, int r);
void fillcircle(int x, int y, int r);
void ellipse(int cx, int cy, int xr, int yr);
void fillellipse(int cx, int cy, int xr, int yr);
void hline(int x1, int x2, int y);
void vline(int y1, int y2, int x);
void rectangle(int left, int top, int right, int bottom);
void bar(int left, int top, int right, int bottom);
void bigpixel(int left, int top, int right, int bottom);
void floodfill(int x, int y, color border);
void filltriangle(int x1, int y1, int x2, int y2, int x3, int y3);

// text
void outtextxy(int x, int y, const std::string& text);
int textwidth(const std::string& text);
int textheight(const std::string& text);
void settextstyle(int font, int direction, int charsize);
void settextjustify(int horizontal, int vertical);

// keyboard
void kbreset();
int kbhit();
bool is_key_pressed(int key);
bool is_key_down(int key);
bool is_key_up(int key);
void set_default_keyboard_callback();
void set_keyboard_callback(std::function<void(int, int, int, int)> callback);

// mouse
void mbreset();
void set_cursor_pos(double x, double y);
std::pair<double, double> get_cursor_pos();
bool is_button_pressed(int button);
bool is_button_down(int button);
bool is_button_up(int button);
int get_button_status();
void set_default_cursor_pos_callback();
void set_raw_cursor_pos_callback();
void set_default_mouse_button_callback();
void set_cursor_pos_callback(std::function<void(double, double)> callback);
void set_mouse_button_callback(std::function<void(int, int, int)> callback);

// time
void delay(int miliseconds);
void show_fps();
void hide_fps();

} // namespace lfbg