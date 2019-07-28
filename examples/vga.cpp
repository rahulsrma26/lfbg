#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int width = 16, height = 16;
    float multiplier = 32;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro, 1);
    for (int y = 0, c = 0; y < 16; y++)
        for (int x = 0; x < 16; x++, c++)
            putpixel(x, y, c);
    apply_palette();

    for (; !closed(); bitblt())
        if (is_key_up(GLFW_KEY_ESCAPE))
            break;

    closegraph();
}
