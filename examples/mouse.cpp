#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int width = 256, height = 256;
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
        if (is_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
            outtextxy(20, 150, "LEFT");
        if (is_button_pressed(GLFW_MOUSE_BUTTON_MIDDLE))
            outtextxy(100, 150, "MIDDLE");
        if (is_button_pressed(GLFW_MOUSE_BUTTON_RIGHT))
            outtextxy(200, 150, "RIGHT");
        bitblt();
    }
    closegraph();
}
