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

template <class T>
struct point2d{
    T x, y;
};

extern color palette[256];

enum class RenderType { Retro, Smooth };

void initgraph(int width, int height, float multiplier = 1, RenderType rt = RenderType::Retro,
               int swap_interval = 0);

void closegraph();

void cleardevice(color c = COLOR::BLACK);

void setcolor(color);

color rgb2color(int r, int g, int b);

color getcolor();

void putpixel(int x, int y, color);

color getpixel(int x, int y);

void line(int x1, int y1, int x2, int y2);

void circle(int x, int y, int r);

void hline(int x1, int x2, int y);

void vline(int y1, int y2, int x);

void rectangle(int left, int top, int right, int bottom);

void bar(int left, int top, int right, int bottom);

void outtextxy(int x, int y, const std::string& text);

// extra

void sleep(double seconds);

bool closed();

void bitblt();

void set_title(const std::string& title);

const std::string& get_title();

void show_fps();

void hide_fps();

int kbhit();

bool is_key_pressed(int key);

bool is_key_down(int key);

bool is_key_up(int key);

} // namespace lfbg