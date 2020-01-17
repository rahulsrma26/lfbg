#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"

void draw_bands() {
    using namespace lfbg;
    for (int r = 0; r < 512; r++)
        for (int g = 0; g < 512; g++)
            putpixel(g, r, rgb2color(r / 2, r / 2, r / 2));
}

void draw_cubes() {
    using namespace lfbg;
    for (int r = 0; r < 512; r++)
        for (int g = 0; g < 512; g++)
            putpixel(r, g, rgb2color(r + g, r + g, r + g));

    for (int r = 0; r < 256; r++)
        for (int g = 0; g < 256; g++)
            for (int b = 0; b < 256; b++)
                putpixel(b + r, g + r, rgb2color(r, g, b));
}

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int w = 512, h = 512;
    float multiplier = 1;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 0);
    cleardevice();

    if (argc > 2) {
        if (std::string(argv[2]) == "cube")
            draw_cubes();
        else
            Image::fromBMP(argv[2]).draw(0, 0);
    } else
        draw_bands();

    vector<string> mode_names = {"Threshold", "Ordered2x2", "Ordered4x4", "FloydSteinberg",
                                 "FilterLite"};
    vector<ColorOptimization> modes = {
        ColorOptimization::Threshold, ColorOptimization::Ordered2x2, ColorOptimization::Ordered4x4,
        ColorOptimization::FloydSteinberg, ColorOptimization::FilterLite};
    int mode = 0;

    bool monocrome = true;
    int bits = 1;
    int rgb_split[9][3] = {{},        {},        {},        {2, 2, 2}, {2, 4, 2},
                           {4, 4, 2}, {4, 4, 4}, {4, 8, 4}, {8, 8, 4}};

    auto set_cols = [&] {
        if (monocrome) {
            int cols = 1 << bits;
            for (int r = 0; r < cols; r++) {
                int v = 255 * r / (cols - 1);
                set_palette(r, rgb2color(v, v, v));
            }
        } else {
            auto& s = rgb_split[bits];
            for (int r = 0, i = 0; r < s[0]; r++)
                for (int g = 0; g < s[1]; g++)
                    for (int b = 0; b < s[2]; b++, i++)
                        set_palette(i, rgb2color(255 * r / (s[0] - 1), 255 * g / (s[1] - 1),
                                                 255 * b / (s[2] - 1)));
        }
        set_title(mode_names[mode] + " bits= " + to_string(bits));
        enable_palette(modes[mode], 1 << bits);
    };

    for (int key = 1; !closed(); key = kbhit()) {
        if (key == GLFW_KEY_LEFT)
            bits = std::clamp(bits - 1, 1, 8);
        if (key == GLFW_KEY_RIGHT)
            bits = std::clamp(bits + 1, 1, 8);
        if (key == GLFW_KEY_UP)
            mode = std::clamp(mode + 1, 0, (int)modes.size() - 1);
        if (key == GLFW_KEY_DOWN)
            mode = std::clamp(mode - 1, 0, (int)modes.size() - 1);
        if (key == GLFW_KEY_M)
            monocrome = !monocrome;
        if (key)
            set_cols();
    }
    lfbg::closegraph();
}
