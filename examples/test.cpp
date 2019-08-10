#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int w = 512, h = 512;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 0);
    cleardevice();
    for (int r = 0, i = 0; r < 8; r++)
        for (int g = 0; g < 8; g++)
            for (int b = 0; b < 4; b++, i++)
                set_palette(i, rgb2color(r << 5, g << 5, b << 6));

    enable_palette();
    restricted_palette(true, Dithering::Ordered);

    for (int r = 0; r < 256; r++)
        for (int g = 0; g < 256; g++)
            for (int b = 0; b < 256; b++)
                putpixel(b + r, 511 - g - r, rgb2color(r, g, b));

    for (int r = 0; r < 256; r++)
        for (int g = 0; g < 256; g++)
            for (int b = 0; b < 256; b++)
                putpixel(b + r, g + r, rgb2color(r, g, b));

    for (; !kbhit(); delay(200))
        if (closed())
            exit(0);
    lfbg::closegraph();
}
