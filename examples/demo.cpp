#include <stdlib.h>
#include <string>
#include <cmath>
#include "lfbg/graphics.h"

using namespace std;
using namespace lfbg;
constexpr int width = 640, height = 400;
float multiplier = 1;

void text_demo() {
    set_title("TEXT");
    string s(16, ' ');
    for (int i = 0; i < 128; i += 16) {
        for (int j = 0; j < 16; j++)
            s[j] = i + j;
        outtextxy(0, 12 * (i / 16), s);
    }
    outtextxy(0, 12 * 8, "press any key for next demo.");
    for (; !kbhit(); delay(200))
        if (closed())
            exit(0);
}

void fillstyle_demo() {
    set_title("FILL STYLES");
    cleardevice();
    setcolor(COLOR::YELLOW);
    const int ox = 30, oy = 25, wm = 120, hm = 90, w = 100, h = 80;
    for (int i = 0, k = 0; i < 4; i++)
        for (int j = 0; j < 5; j++, k++) {
            setfillstyle(k, COLOR::WHITE);
            bar(ox + wm * j, oy + hm * i, ox + wm * j + w, oy + hm * i + h);
            rectangle(ox + wm * j, oy + hm * i, ox + wm * j + w, oy + hm * i + h);
        }
    for (; !kbhit(); delay(200))
        if (closed())
            exit(0);
}

void random_pixel_demo() {
    set_title("RANDOM PIXELS");
    cleardevice();
    while (!kbhit())
        putpixel(rand() % width, rand() % height, rgb2color(rand(), rand(), rand()));
}

void random_line_demo() {
    set_title("RANDOM LINES");
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int x1 = rand() % width, y1 = rand() % height;
        int x2 = rand() % width, y2 = rand() % height;
        line(x1, y1, x2, y2);
    }
}

void random_circle_demo() {
    set_title("RANDOM CIRCLES");
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        circle(rand() % width, rand() % height, rand() % r);
    }
}

void random_ellipse_demo() {
    set_title("RANDOM ELLIPSES");
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        ellipse(rand() % width, rand() % height, rand() % r, rand() % r);
    }
}

void random_arc_demo() {
    set_title("RANDOM ARCS");
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        arc(rand() % width, rand() % height, rand() % 360, rand() % 360, rand() % r);
    }
}

void random_rectangle_demo() {
    set_title("RANDOM RECTANGLES");
    cleardevice();
    while (!kbhit()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        rectangle(left, top, right, bottom);
    }
}

void random_fillcircle_demo() {
    set_title("RANDOM FILLED CIRCLES");
    cleardevice();
    const int radius = (width + height) / 4;
    while (!kbhit()) {
        auto c = rgb2color(rand(), rand(), rand());
        auto w = rand() % width;
        auto h = rand() % height;
        auto r = rand() % radius;
        setfillstyle(rand() % 11, c);
        fillcircle(w, h, r);
        setcolor(c);
        circle(w, h, r);
        if (closed())
            exit(0);
    }
}

void random_fillellipse_demo() {
    set_title("RANDOM FILLED ELLIPSES");
    cleardevice();
    while (!kbhit()) {
        auto c = rgb2color(rand(), rand(), rand());
        auto w = rand() % width;
        auto h = rand() % height;
        auto rx = rand() % (width/4);
        auto ry = rand() % (height/4);
        setfillstyle(rand() % 11, c);
        fillellipse(w, h, rx, ry);
        setcolor(c);
        ellipse(w, h, rx, ry);
        if (closed())
            exit(0);
    }
}

void random_bar_demo() {
    set_title("RANDOM BAR");
    cleardevice();
    while (!kbhit()) {
        auto c = rgb2color(rand(), rand(), rand());
        setfillstyle(rand() % 11, c);
        setcolor(c);
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        bar(left, top, right, bottom);
        rectangle(left, top, right, bottom);
        if (closed())
            exit(0);
    }
}

void polygon_line_demo() {
    set_title("POLYGON LINES");
    cleardevice();
    setcolor(COLOR::WHITE);
    constexpr int lim = 14;
    int x[lim], y[lim], r = (height - 1) / 2;
    for (int i = 0; i < lim; i++) {
        x[i] = width / 2 + r * sin(2 * 3.1415 * i / (lim - 1));
        y[i] = height / 2 + r * cos(2 * 3.1415 * i / (lim - 1));
    }
    for (int i = 0; i < lim; i++)
        for (int j = i + 1; j < lim; j++)
            line(x[i], y[i], x[j], y[j]);
    for (; !kbhit(); delay(200))
        if (closed())
            exit(0);
}

int main(int argc, char* argv[]) {
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro);
    text_demo();
    random_pixel_demo();
    random_line_demo();
    fillstyle_demo();
    random_circle_demo();
    random_fillcircle_demo();
    random_ellipse_demo();
    random_fillellipse_demo();
    random_arc_demo();
    random_rectangle_demo();
    random_bar_demo();
    polygon_line_demo();
    closegraph();
}
