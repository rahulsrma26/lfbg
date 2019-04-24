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

    initgraph(width, height, multiplier, RenderType::Retro);
    string s(16, ' ');
    for (int i = 0; i < 128; i += 16) {
        for (int j = 0; j < 16; j++)
            s[j] = i + j;
        outtextxy(0, 12 * (i / 16), s);
    }
    while (not_closed()) {
        putpixel(rand() % width, rand() % height, rand() & 0xffffff);
        bitblt();
    }
    closegraph();
}
