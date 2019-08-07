#include <stdlib.h>
#include <string>
#include <cmath>
#include "lfbg/graphics.h"

using namespace std;
using namespace lfbg;
constexpr int width = 640, height = 400;
float multiplier = 1;

void wait() {
    for (; !kbhit(); delay(200))
        if (closed())
            exit(0);
    if (closed())
        exit(0);
}

void status_report() {
    setcolor(COLOR::WHITE);
    do {
        cleardevice();
        int y = 10, g = 20;
        settextjustify(TEXT::CENTER, TEXT::CENTER);
        outtextxy(width / 2, y, "STATUS REPORT");
        outtextxy(width / 2, height - 10, "Press Esc to end or any other key for next demo");
        rectangle(0, 20, width - 1, height - 20);

        settextjustify(TEXT::RIGHT, TEXT::CENTER);
        outtextxy(width / 2, y += g, "Window Resolution");
        auto [wx, wy] = get_window_size();
        settextjustify(TEXT::LEFT, TEXT::CENTER);
        outtextxy(width / 2, y, ": " + to_string(wx) + " x " + to_string(wy));

        settextjustify(TEXT::RIGHT, TEXT::CENTER);
        outtextxy(width / 2, y += g, "Screen Resolution");
        auto [bx, by] = get_buffer_size();
        settextjustify(TEXT::LEFT, TEXT::CENTER);
        outtextxy(width / 2, y, ": " + to_string(bx) + " x " + to_string(by));

        settextjustify(TEXT::RIGHT, TEXT::CENTER);
        outtextxy(width / 2, y += g, "Cursor position");
        auto [cx, cy] = get_cursor_pos();
        settextjustify(TEXT::LEFT, TEXT::CENTER);
        outtextxy(width / 2, y, ": " + to_string(cx) + " x " + to_string(cy));

        settextjustify(TEXT::RIGHT, TEXT::CENTER);
        outtextxy(width / 2, y += g, "Mouse buttons");
        int b = get_button_status();
        string bs = "";
        if (b & 1)
            bs += "LEFT ";
        if (b & 2)
            bs += "RIGHT ";
        if (b & 4)
            bs += "MIDDLE ";
        settextjustify(TEXT::LEFT, TEXT::CENTER);
        outtextxy(width / 2, y, ": " + bs);

        if (closed())
            exit(0);
    } while (!kbhit());
}

void text_demo() {
    cleardevice();
    setcolor(COLOR::WHITE);
    settextjustify(TEXT::CENTER, TEXT::CENTER);
    settextstyle(0, 0, 1);
    outtextxy(width / 2, 20, "All text character with ASCII codes");
    settextjustify(TEXT::LEFT, TEXT::TOP);
    setfillstyle(1, COLOR::DARK_GRAY);
    int xo = 10, yo = 80, xm = 40, ym = 40;
    for (int i = 0, k = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++, k++) {
            bar(xo + j * xm, yo + i * ym, xo + j * xm + 15, yo + i * ym + 23);
            settextstyle(0, 0, 1);
            outtextxy(xo + j * xm, yo + i * ym - 12, to_string(k));
            settextstyle(0, 0, 2);
            string s = " ";
            s[0] = k;
            outtextxy(xo + j * xm, yo + i * ym, s);
        }
    }
    wait();
}

void fillstyle_demo() {
    cleardevice();
    setcolor(COLOR::WHITE);
    settextjustify(TEXT::CENTER, TEXT::CENTER);
    settextstyle(0, 0, 1);
    outtextxy(width / 2, 20, "All fill styles");

    settextjustify(TEXT::RIGHT, TEXT::CENTER);
    setcolor(COLOR::CYAN);

    const int ox = 30, oy = 40, wm = 120, hm = 90, w = 90, h = 80;
    for (int i = 0, k = 0; i < 4; i++)
        for (int j = 0; j < 5; j++, k++) {
            setfillstyle(k, COLOR::WHITE);
            bar(ox + wm * j, oy + hm * i, ox + wm * j + w, oy + hm * i + h);
            rectangle(ox + wm * j, oy + hm * i, ox + wm * j + w, oy + hm * i + h);
            outtextxy(ox + wm * j, oy + hm * i + h / 2, to_string(k));
        }
    wait();
}

void custom_fillstyle_demo() {
    cleardevice();
    setcolor(COLOR::WHITE);
    settextjustify(TEXT::CENTER, TEXT::CENTER);
    settextstyle(0, 0, 1);
    outtextxy(width / 2, 20, "Custom fill pattern");

    // 00000000
    // 01111110
    // 01010100
    // 01101000
    // 01010000
    // 01100000
    // 01000000
    // 00000000
    uint64_t pattern = 0b0000000001111110010101000110100001010000011000000100000000000000;
    settextjustify(TEXT::LEFT, TEXT::TOP);
    string str = "12345678";

    outtextxy(20, 60, "setfillpattern(int64_t)");
    outtextxy(58, 110, "MSB");
    outtextxy(208, 310, "LSB");
    hline(80, 200, 315);
    line(80, 315, 85, 310);
    line(80, 315, 85, 320);
    vline(130, 310, 68);
    line(68, 130, 63, 135);
    line(68, 130, 73, 135);

    settextstyle(0, 0, 2);
    for (int i = 0; i < 8; i++) {
        for (int j = 0, k = (pattern >> (56 - 8 * i)); j < 8; j++, k <<= 1)
            str[j] = (k & 0x80) ? '1' : '0';
        outtextxy(80, 120 + i * 24, str);
    }
    setfillpattern(pattern);
    bar(width / 2, 64, width - 20, height - 32);
    rectangle(width / 2, 64, width - 20, height - 32);
    wait();
}

void random_pixel_demo() {
    cleardevice();
    while (!kbhit() && !closed())
        putpixel(rand() % width, rand() % height, rgb2color(rand(), rand(), rand()));
    if (closed())
        exit(0);
}

void random_line_demo() {
    cleardevice();
    while (!kbhit() && !closed()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int x1 = rand() % width, y1 = rand() % height;
        int x2 = rand() % width, y2 = rand() % height;
        line(x1, y1, x2, y2);
    }
    if (closed())
        exit(0);
}

void random_circle_demo() {
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit() && !closed()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        circle(rand() % width, rand() % height, rand() % r);
    }
    if (closed())
        exit(0);
}

void random_ellipse_demo() {
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit() && !closed()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        ellipse(rand() % width, rand() % height, rand() % r, rand() % r);
    }
    if (closed())
        exit(0);
}

void random_arc_demo() {
    cleardevice();
    const int r = (width + height) / 4;
    while (!kbhit() && !closed()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        arc(rand() % width, rand() % height, rand() % 360, rand() % 360, rand() % r);
    }
    if (closed())
        exit(0);
}

void random_rectangle_demo() {
    cleardevice();
    while (!kbhit() && !closed()) {
        setcolor(rgb2color(rand(), rand(), rand()));
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        rectangle(left, top, right, bottom);
    }
    if (closed())
        exit(0);
}

void random_fillcircle_demo() {
    cleardevice();
    const int radius = (width + height) / 4;
    while (!kbhit() && !closed()) {
        auto c = rgb2color(rand(), rand(), rand());
        auto w = rand() % width;
        auto h = rand() % height;
        auto r = rand() % radius;
        setfillstyle(rand() % 11, c);
        fillcircle(w, h, r);
        setcolor(c);
        circle(w, h, r);
    }
    if (closed())
        exit(0);
}

void random_fillellipse_demo() {
    cleardevice();
    while (!kbhit() && !closed()) {
        auto c = rgb2color(rand(), rand(), rand());
        auto w = rand() % width;
        auto h = rand() % height;
        auto rx = rand() % (width / 4);
        auto ry = rand() % (height / 4);
        setfillstyle(rand() % 11, c);
        fillellipse(w, h, rx, ry);
        setcolor(c);
        ellipse(w, h, rx, ry);
    }
    if (closed())
        exit(0);
}

void random_bar_demo() {
    cleardevice();
    while (!kbhit() && !closed()) {
        auto c = rgb2color(rand(), rand(), rand());
        setfillstyle(rand() % 11, c);
        setcolor(c);
        int left = rand() % width, top = rand() % height;
        int right = rand() % width, bottom = rand() % height;
        bar(left, top, right, bottom);
        rectangle(left, top, right, bottom);
    }
    if (closed())
        exit(0);
}

void polygon_line_demo() {
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
    wait();
}

void random_filltriangle_demo() {
    cleardevice();
    do {
        setfillstyle(1, rgb2color(rand(), rand(), rand()));
        filltriangle(rand() % width, rand() % height, rand() % width, rand() % height,
                     rand() % width, rand() % height);
        if (closed())
            exit(0);
    } while (!kbhit());
}

int main(int argc, char* argv[]) {
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro);
    set_title("DEMO");
    status_report();
    text_demo();
    fillstyle_demo();
    custom_fillstyle_demo();
    random_pixel_demo();
    random_line_demo();
    random_circle_demo();
    random_fillcircle_demo();
    random_ellipse_demo();
    random_fillellipse_demo();
    random_arc_demo();
    random_rectangle_demo();
    random_bar_demo();
    polygon_line_demo();
    random_filltriangle_demo();
    closegraph();
}
