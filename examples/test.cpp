#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int width = 320, height = 200;
    float multiplier = 2;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro, 1);
    setcolor(COLOR::WHITE);
    circle(width / 2, height / 2, 50);
    circle(width / 2, height / 2, 51);
    setcolor(COLOR::GREEN);
    floodfill(width / 2, height / 2, COLOR::WHITE);

    for (; !closed(); bitblt())
        if (is_key_up(GLFW_KEY_ESCAPE))
            break;

    closegraph();
}
