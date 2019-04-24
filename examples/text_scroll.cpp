#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int width = 320, height = 200;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro, 1);
    string t = "<Press arrow keys>";
    int tx = 50, ty = 10, dx = 1, dy = 1;
    bool manual = false;
    while (not_closed()) {
        cleardevice(0x773333);
        outtextxy(tx, ty, t);
        if (is_pressed(GLFW_KEY_LEFT))
            tx--, manual = true;
        if (is_pressed(GLFW_KEY_RIGHT))
            tx++, manual = true;
        if (is_pressed(GLFW_KEY_UP))
            ty--, manual = true;
        if (is_pressed(GLFW_KEY_DOWN))
            ty++, manual = true;
        if (!manual) {
            tx += dx;
            if (tx < 0 || tx + 8 * t.length() >= width)
                dx *= -1;
            ty += dy;
            if (ty < 0 || ty + 12 >= height)
                dy *= -1;
        }
        bitblt();
    }
    closegraph();
}
