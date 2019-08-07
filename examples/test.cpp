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

    initgraph(w, h, multiplier, RenderType::Retro, 0);
    cleardevice();

    do {
        setfillstyle(1, rgb2color(rand(), rand(), rand()));
        filltriangle(rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
        if (closed())
            exit(0);
    } while (!kbhit());
    lfbg::closegraph();
}
