#pragma once

#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include "linmath.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace lfbg {
typedef uint32_t color;

enum class RenderType { Retro, Smooth };

bool is_pressed(int key);

void cleardevice(color c = 0);

void set_title(const std::string& title);

const std::string& get_title();

void show_fps();

void hide_fps();

void initgraph(int width, int height, float multiplier = 1, RenderType rt = RenderType::Retro,
               int swap_interval = 0);

void closegraph();

void putpixel(int x, int y, color c);

color& getpixel(int x, int y);

void outtextxy(int x, int y, const std::string& text);

bool not_closed();

void bitblt();

} // namespace lfbg