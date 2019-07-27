#include <stdlib.h>
#include <string>
#include <cmath>
#include "lfbg/graphics.h"

using namespace std;
using namespace lfbg;
constexpr int width = 640, height = 400;
float multiplier = 1;

void text_demo() {
    string s(16, ' ');
    for (int i = 0; i < 128; i += 16) {
        for (int j = 0; j < 16; j++)
            s[j] = i + j;
        outtextxy(0, 12 * (i / 16), s);
    }
    outtextxy(0, 12 * 8, "press any key for next demo.");
    while (!kbhit())
        sleep(1);
}

void random_pixel_demo() {
    cleardevice();
    while (!kbhit())
        putpixel(rand() % width, rand() % height, rgb2color(rand(), rand(), rand()));
}

void random_line_demo() {
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int x1 = rand() % width, y1 = rand() % height;
        int x2 = rand() % width, y2 = rand() % height;
        line(x1, y1, x2, y2);
    }
}

void random_circle_demo() {
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int x = rand() % width, y = rand() % height, r = rand() % ((width + height) / 4);
        circle(x, y, r);
    }
}

void random_rectangle_demo() {
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        rectangle(left, top, right, bottom);
    }
}

void random_bar_demo() {
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        bar(left, top, right, bottom);
    }
}

void polygon_line_demo() {
    cleardevice();
    setcolor(COLOR::WHITE);
    constexpr int lim = 14;
    int x[lim], y[lim], r = height / 2;
    for (int i = 0; i < lim; i++) {
        x[i] = width / 2 + r * sin(2 * 3.1415 * i / (lim - 1));
        y[i] = height / 2 + r * cos(2 * 3.1415 * i / (lim - 1));
    }
    for (int i = 0; i < lim; i++)
        for (int j = i + 1; j < lim; j++)
            line(x[i], y[i], x[j], y[j]);
    while (!kbhit())
        sleep(1);
}

int main(int argc, char* argv[]) {
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro);
    text_demo();
    random_pixel_demo();
    random_line_demo();
    random_circle_demo();
    random_rectangle_demo();
    random_bar_demo();
    polygon_line_demo();
    closegraph();
}
