#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int w = 320, h = 480;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    enable_palette();
    cleardevice(1);
    setcolor(7);
    vline(0, h - 1, w / 2);
    for (int i = 1; i <= 6; i++) {
        settextstyle(1, 0, i);
        // int h = textheight("H");
        int y = 20 + i * 50;
        setcolor(12);
        hline(0, w - 1, y);
        // setcolor(11);
        // hline(0, w - 1, y + h);
        setcolor(15);
        outtextxy(w / 2, y, "SIZE " + to_string(i));
    }
    // setcolor(COLOR::GREEN);
    // hline(0, w, 100);

    for (; !closed(); bitblt())
        if (is_key_up(GLFW_KEY_ESCAPE))
            break;

    lfbg::closegraph();
}
