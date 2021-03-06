#include "lfbg/graphics.h"

namespace lfbg {

typedef std::vector<std::vector<int>> matrix;

extern int __screen_width__, __screen_height__;

bool __use_palette__ = false;
ColorOptimization __color_optimization__ = ColorOptimization::None;
int __palette_size__ = 256;
std::vector<color> __palette_output_buffer__;

color __palette__[256] = { // Default VGA Palette
    0x000000, 0x000080, 0x008000, 0x008080, 0x800000, 0x800080, 0x808000, 0xc0c0c0, 0x808080,
    0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff, 0x000000, 0x5f0000,
    0x870000, 0xaf0000, 0xd70000, 0xff0000, 0x005f00, 0x5f5f00, 0x875f00, 0xaf5f00, 0xd75f00,
    0xff5f00, 0x008700, 0x5f8700, 0x878700, 0xaf8700, 0xd78700, 0xff8700, 0x00af00, 0x5faf00,
    0x87af00, 0xafaf00, 0xd7af00, 0xffaf00, 0x00d700, 0x5fd700, 0x87d700, 0xafd700, 0xd7d700,
    0xffd700, 0x00ff00, 0x5fff00, 0x87ff00, 0xafff00, 0xd7ff00, 0xffff00, 0x00005f, 0x5f005f,
    0x87005f, 0xaf005f, 0xd7005f, 0xff005f, 0x005f5f, 0x5f5f5f, 0x875f5f, 0xaf5f5f, 0xd75f5f,
    0xff5f5f, 0x00875f, 0x5f875f, 0x87875f, 0xaf875f, 0xd7875f, 0xff875f, 0x00af5f, 0x5faf5f,
    0x87af5f, 0xafaf5f, 0xd7af5f, 0xffaf5f, 0x00d75f, 0x5fd75f, 0x87d75f, 0xafd75f, 0xd7d75f,
    0xffd75f, 0x00ff5f, 0x5fff5f, 0x87ff5f, 0xafff5f, 0xd7ff5f, 0xffff5f, 0x000087, 0x5f0087,
    0x870087, 0xaf0087, 0xd70087, 0xff0087, 0x005f87, 0x5f5f87, 0x875f87, 0xaf5f87, 0xd75f87,
    0xff5f87, 0x008787, 0x5f8787, 0x878787, 0xaf8787, 0xd78787, 0xff8787, 0x00af87, 0x5faf87,
    0x87af87, 0xafaf87, 0xd7af87, 0xffaf87, 0x00d787, 0x5fd787, 0x87d787, 0xafd787, 0xd7d787,
    0xffd787, 0x00ff87, 0x5fff87, 0x87ff87, 0xafff87, 0xd7ff87, 0xffff87, 0x0000af, 0x5f00af,
    0x8700af, 0xaf00af, 0xd700af, 0xff00af, 0x005faf, 0x5f5faf, 0x875faf, 0xaf5faf, 0xd75faf,
    0xff5faf, 0x0087af, 0x5f87af, 0x8787af, 0xaf87af, 0xd787af, 0xff87af, 0x00afaf, 0x5fafaf,
    0x87afaf, 0xafafaf, 0xd7afaf, 0xffafaf, 0x00d7af, 0x5fd7af, 0x87d7af, 0xafd7af, 0xd7d7af,
    0xffd7af, 0x00ffaf, 0x5fffaf, 0x87ffaf, 0xafffaf, 0xd7ffaf, 0xffffaf, 0x0000d7, 0x5f00d7,
    0x8700d7, 0xaf00d7, 0xd700d7, 0xff00d7, 0x005fd7, 0x5f5fd7, 0x875fd7, 0xaf5fd7, 0xd75fd7,
    0xff5fd7, 0x0087d7, 0x5f87d7, 0x8787d7, 0xaf87d7, 0xd787d7, 0xff87d7, 0x00afd7, 0x5fafd7,
    0x87afd7, 0xafafd7, 0xd7afd7, 0xffafd7, 0x00d7d7, 0x5fd7d7, 0x87d7d7, 0xafd7d7, 0xd7d7d7,
    0xffd7d7, 0x00ffd7, 0x5fffd7, 0x87ffd7, 0xafffd7, 0xd7ffd7, 0xffffd7, 0x0000ff, 0x5f00ff,
    0x8700ff, 0xaf00ff, 0xd700ff, 0xff00ff, 0x005fff, 0x5f5fff, 0x875fff, 0xaf5fff, 0xd75fff,
    0xff5fff, 0x0087ff, 0x5f87ff, 0x8787ff, 0xaf87ff, 0xd787ff, 0xff87ff, 0x00afff, 0x5fafff,
    0x87afff, 0xafafff, 0xd7afff, 0xffafff, 0x00d7ff, 0x5fd7ff, 0x87d7ff, 0xafd7ff, 0xd7d7ff,
    0xffd7ff, 0x00ffff, 0x5fffff, 0x87ffff, 0xafffff, 0xd7ffff, 0xffffff, 0x080808, 0x121212,
    0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a, 0x444444, 0x4e4e4e, 0x585858, 0x626262, 0x6c6c6c,
    0x767676, 0x808080, 0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6,
    0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee};

constexpr int __palette_r_bits__ = 6;
constexpr int __palette_g_bits__ = 7;
constexpr int __palette_b_bits__ = 6;
constexpr int __palette_r_size__ = 1 << __palette_r_bits__;
constexpr int __palette_g_size__ = 1 << __palette_g_bits__;
constexpr int __palette_b_size__ = 1 << __palette_b_bits__;

unsigned char __reverse_palette__[__palette_r_size__ * __palette_g_size__ * __palette_b_size__];

void calc_palette() {
    for (int r = 0; r < __palette_r_size__; r++)
        for (int g = 0; g < __palette_g_size__; g++)
            for (int b = 0; b < __palette_b_size__; b++) {
                int mind = 1 << 24, mini = 0;
                for (int i = 0; i < __palette_size__; i++) {
                    int x = (__palette__[i] & 255) >> (8 - __palette_r_bits__);
                    int y = ((__palette__[i] >> 8) & 255) >> (8 - __palette_g_bits__);
                    int z = ((__palette__[i] >> 16) & 255) >> (8 - __palette_b_bits__);
                    int d = (r - x) * (r - x) + (g - y) * (g - y) + (b - z) * (b - z);
                    if (d < mind) {
                        mind = d;
                        mini = i;
                    }
                }
                __reverse_palette__[(b << (__palette_r_bits__ + __palette_g_bits__)) |
                                    (g << __palette_r_bits__) | r] = mini;
            }
}

inline uint8_t nearest_palette_color(color c) {
    int r = (c & 255) >> (8 - __palette_r_bits__);
    int g = ((c >> 8) & 255) >> (8 - __palette_g_bits__);
    int b = ((c >> 16) & 255) >> (8 - __palette_b_bits__);
    return __reverse_palette__[(b << (__palette_r_bits__ + __palette_g_bits__)) |
                               (g << __palette_r_bits__) | r];
}

void enable_palette(ColorOptimization co, int palette_size) {
    __use_palette__ = true;
    __palette_size__ = std::clamp(palette_size, 1, 256);
    __color_optimization__ = co;
    if (__color_optimization__ != ColorOptimization::None)
        calc_palette();
}

void disable_palette() { __use_palette__ = false; }

bool using_palette() { return __use_palette__; }

void FloydSteinberg(std::vector<color>& output, const std::vector<color>& input) {
    std::copy(input.begin(), input.end(), output.begin());
    for (int i = 0, k = 0; i < __screen_height__; i++)
        for (int j = 0; j < __screen_width__; j++, k++) {
            color old = output[k];
            uint8_t* c1 = (uint8_t*)&old;
            output[k] = __palette__[nearest_palette_color(output[k])];
            uint8_t* c = (uint8_t*)&output[k];
            for (int l = 0; l < 3; l++) {
                int e = (int)(c1[l]) - c[l];
                if (j + 1 < __screen_width__)
                    c[l + 4] = std::clamp((int)(c[l + 4]) + e * 7 / 16, 0, 255);
                if (j - 1 >= 0 && i + 1 < __screen_height__) {
                    const int idx = l + 4 * __screen_width__ - 1;
                    c[idx] = std::clamp(int(c[idx]) + e * 3 / 16, 0, 255);
                }
                if (i + 1 < __screen_height__) {
                    const int idx = l + 4 * __screen_width__;
                    c[idx] = std::clamp((int)(c[idx]) + e * 5 / 16, 0, 255);
                }
                if (j + 1 < __screen_width__ && i + 1 < __screen_height__) {
                    const int idx = l + 4 * __screen_width__ + 1;
                    c[idx] = std::clamp((int)(c[idx]) + e * 1 / 16, 0, 255);
                }
            }
        }
}

void FilterLite(std::vector<color>& output, const std::vector<color>& input) {
    std::copy(input.begin(), input.end(), output.begin());
    for (int i = 0, k = 0; i < __screen_height__; i++)
        for (int j = 0; j < __screen_width__; j++, k++) {
            color old = output[k];
            uint8_t* c1 = (uint8_t*)&old;
            output[k] = __palette__[nearest_palette_color(output[k])];
            uint8_t* c = (uint8_t*)&output[k];
            for (int l = 0; l < 3; l++) {
                int e = (int)(c1[l]) - c[l];
                if (j + 1 < __screen_width__)
                    c[l + 4] = std::clamp((int)(c[l + 4]) + e / 2, 0, 255);
                if (j - 1 >= 0 && i + 1 < __screen_height__) {
                    const int idx = l + 4 * __screen_width__ - 1;
                    c[idx] = std::clamp(int(c[idx]) + e / 4, 0, 255);
                }
                if (i + 1 < __screen_height__) {
                    const int idx = l + 4 * __screen_width__;
                    c[idx] = std::clamp((int)(c[idx]) + e / 4, 0, 255);
                }
            }
        }
}

void Ordered2x2(std::vector<color>& output, const std::vector<color>& input) {
    int m[2][2] = {{0, 2}, {3, 1}};
    for (int i = 0, k = 0; i < __screen_height__; i++)
        for (int j = 0; j < __screen_width__; j++, k++) {
            auto c0 = (const uint8_t*)&input[k];
            auto c1 = (uint8_t*)&output[k];
            for (int l = 0; l < 3; l++)
                c1[l] = std::clamp(
                    (int)(c0[l]) + (2 * m[i & 1][j & 1] - 3) * 31 / (__palette_size__ - 1), 0, 255);
            output[k] = __palette__[nearest_palette_color(output[k])];
        }
}

void Ordered4x4(std::vector<color>& output, const std::vector<color>& input) {
    int m[4][4] = {{0, 12, 3, 15}, {8, 4, 11, 7}, {2, 14, 1, 13}, {10, 6, 9, 5}};
    for (int i = 0, k = 0; i < __screen_height__; i++)
        for (int j = 0; j < __screen_width__; j++, k++) {
            auto c0 = (const uint8_t*)&input[k];
            auto c1 = (uint8_t*)&output[k];
            for (int l = 0; l < 3; l++)
                c1[l] = std::clamp(
                    (int)(c0[l]) + (2 * m[i & 3][j & 3] - 15) * 7 / (__palette_size__ - 1), 0, 255);
            output[k] = __palette__[nearest_palette_color(output[k])];
        }
}

std::vector<color>& apply_palette(const std::vector<color>& buffer) {
    const size_t n = buffer.size();
    if (__palette_output_buffer__.size() != n)
        __palette_output_buffer__.resize(n);
    switch (__color_optimization__) {
        case ColorOptimization::Threshold:
            for (size_t i = 0; i < n; i++)
                __palette_output_buffer__[i] = __palette__[nearest_palette_color(buffer[i])];
            break;
        case ColorOptimization::FloydSteinberg:
            FloydSteinberg(__palette_output_buffer__, buffer);
            break;
        case ColorOptimization::FilterLite:
            FilterLite(__palette_output_buffer__, buffer);
            break;
        case ColorOptimization::Ordered2x2: Ordered2x2(__palette_output_buffer__, buffer); break;
        case ColorOptimization::Ordered4x4: Ordered4x4(__palette_output_buffer__, buffer); break;
        default:
            for (size_t i = 0; i < n; i++)
                __palette_output_buffer__[i] = __palette__[buffer[i] & 0xff];
    }
    return __palette_output_buffer__;
}

void set_palette(int idx, color c) { __palette__[idx & 0xff] = c; }

color get_palette(int idx) { return __palette__[idx & 0xff]; }

} // namespace lfbg