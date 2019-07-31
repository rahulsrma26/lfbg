#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int w = 640, h = 480;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 1);
    enable_palette();
    auto show = [=](int x, int y, const string& t) {
        setcolor(7);
        vline(0, h - 1, x);
        hline(0, w - 1, y);
        setcolor(15);
        outtextxy(x, y, t);
    };

    int hori = 1, vert = 1;
    string shori[] = {"LEFT", "CENTER", "RIGHT"};
    string svert[] = {"TOP", "CENTER", "BOTTOM"};

    for (int key = 1; !closed(); key = kbhit()) {
        cleardevice(1);
        settextjustify(hori, vert);
        settextstyle(1, 0, 4);
        show(220, 160, "RAHUL");
        settextstyle(1, 1, 4);
        show(440, 160, "RAHUL");
        settextstyle(1, 2, 4);
        show(440, 320, "RAHUL");
        settextstyle(1, 3, 4);
        show(220, 320, "RAHUL");

        switch (key) {
            case GLFW_KEY_LEFT: hori = max(hori - 1, 0); break;
            case GLFW_KEY_RIGHT: hori = min(hori + 1, 2); break;
            case GLFW_KEY_UP: vert = max(vert - 1, 0); break;
            case GLFW_KEY_DOWN: vert = min(vert + 1, 2); break;
            case GLFW_KEY_ESCAPE: closegraph(); exit(0);
        }
        if (key)
            set_title(shori[hori] + ":" + svert[vert]);
    }

    lfbg::closegraph();
}
