#pragma once

#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include "linmath.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <chrono>
#include <thread>
#include <functional>
#include <cmath>

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

enum class RenderType { Retro, Smooth };

// core
GLFWwindow* initgraph(int width, int height, float multiplier = 1,
                      RenderType rt = RenderType::Retro, int swap_interval = 0);
void closegraph();
void bitblt();

// basic drawing
void cleardevice(color c = COLOR::BLACK);
void putpixel(int x, int y, color);
color getpixel(int x, int y);
void apply_palette();
void set_palette(int idx, color);
color get_palette(int idx);

// advance drawing
void setcolor(color);
color getcolor();
void line(int x1, int y1, int x2, int y2);
void circle(int x, int y, int r);
void hline(int x1, int x2, int y);
void vline(int y1, int y2, int x);
void rectangle(int left, int top, int right, int bottom);
void bar(int left, int top, int right, int bottom);
void floodfill(int x, int y, color border);
void outtextxy(int x, int y, const std::string& text);

// info
bool closed();
std::pair<int, int> get_buffer_size();
std::pair<int, int> get_window_size();
std::pair<double, double> get_cursor_pos();
int kbhit();
bool is_key_pressed(int key);
bool is_key_down(int key);
bool is_key_up(int key);
bool is_button_pressed(int button);
bool is_button_down(int button);
bool is_button_up(int button);

// misc
color rgb2color(int r, int g, int b);
void delay(int miliseconds);
void set_title(const std::string& title);
const std::string& get_title();
void show_fps();
void hide_fps();

// callbacks
void set_keyboard_callback(std::function<void(int, int, int, int)> callback);
void set_cursor_pos_callback(std::function<void(double, double)> callback);
void set_mouse_button_callback(std::function<void(int, int, int)> callback);
void set_default_window_resize_callback();
void set_default_keyboard_callback();
void set_default_cursor_pos_callback();
void set_default_mouse_button_callback();

} // namespace lfbg