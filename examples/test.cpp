#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int w = 320, h = 240;
    float multiplier = 2;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 1);
    setcolor(COLOR::BLUE);
    for (int i = 0, k = 0; i < 4; i++)
        for (int j = 0; j < 5; j++, k++) {
            setfillstyle(k, COLOR::WHITE);
            bar(10 + 60 * j, 10 + 60 * i, 10 + 60 * j + 40, 10 + 60 * i + 40);
            rectangle(10 + 60 * j, 10 + 60 * i, 10 + 60 * j + 40, 10 + 60 * i + 40);
        }

    for (; !closed(); bitblt())
        if (is_key_up(GLFW_KEY_ESCAPE))
            break;

    lfbg::closegraph();
}
