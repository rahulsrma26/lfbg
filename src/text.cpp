#include "lfbg/graphics.h"

namespace lfbg {

namespace TEXT {
const int LEFT = 0;
const int RIGHT = 2;
const int TOP = 0;
const int BOTTOM = 2;
const int CENTER = 1;
} // namespace TEXT

// external objects

extern int __screen_width__, __screen_height__;
extern std::vector<color> __screen_buffer__;
extern color __foreground_color__;

// defined objects
int __font__ = 0, __text_direction__ = 0, __text_size__ = 1;
int __text_justify_horizontal__ = TEXT::LEFT;
int __text_justify_vertical__ = TEXT::TOP;

float __font_scales__[11] = {1, 0.6, 0.66, 0.75, 1, 1.33, 1.66, 2, 2.5, 3, 4};
const char* __fontfiles__[11] = {"",         "TRIP.CHR", "LITT.CHR", "SANS.CHR",
                                 "GOTH.CHR", "SCRI.CHR", "SIMP.CHR", "TSCR.CHR",
                                 "LCOM.CHR", "EURO.CHR", "BOLD.CHR"};

uint32_t __default_font__[128 * 3] = {
    0,          0,          0,          2177072640, 2579333541, 32451,      4294934016, 3888381915,
    32511,      1998716928, 1048543103, 2076,       1042024448, 473857919,  8,          1010571264,
    417851391,  32280,      2117867520, 410976255,  32280,      0,          1014922812, 0,
    4294967295, 3280044483, 4294967295, 2117861376, 1715618406, 15486,      2177105919, 2579348889,
    4294951809, 1550875648, 858988366,  7731,       1717976064, 2115517542, 6168,       2560161792,
    504895736,  3615,       4274454016, 3871786694, 223207,     3675783168, 2129127294, 6363,
    117637376,  119504671,  259,        1885356032, 1887207292, 16480,      2117867520, 2115508248,
    6204,       1717986816, 26214,      26214,      3688627712, 3638091483, 55512,      214334976,
    1013343804, 8282928,    0,          2130706432, 32639,      2117867520, 2115508248, 8263740,
    2117867520, 404232216,  6168,       404232192,  2115508248, 6204,       402653184,  405831472,
    0,          201326592,  201752326,  0,          0,          2130903811, 0,          603979776,
    610729830,  0,          134742016,  1044257820, 32639,      2139029504, 471612990,  2056,
    0,          0,          0,          505285632,  789534,     3084,       1717986816, 36,
    0,          2134259200, 2134259254, 13878,      54397964,   808459779,  789535,     587202560,
    101455923,  12595,      454757888,  863723278,  28219,      202116096,  6,          0,
    202911744,  201721350,  12312,      403441152,  405811248,  1548,       1711276032, 1715273532,
    0,          402653184,  404258328,  0,          0,          0,          400412,     0,
    32512,      0,          0,          0,          7196,       1614807040, 101455920,  259,
    1935883776, 1735355259, 15971,      252446720,  202116108,  16140,      858988032,  101455920,
    16179,      808656384,  808459312,  7731,       1010315264, 813642550,  30768,      50544384,
    808460035,  7731,       50732032,   858988291,  7731,       1667464960, 202911840,  3084,
    858988032,  859512375,  7731,       858988032,  404241971,  3596,       469762048,  469762076,
    28,         469762048,  469762076,  792604,     202911744,  201720582,  12312,      0,
    8257662,    0,          403441152,  405823536,  1548,       808656384,  789528,     3084,
    1667448320, 58424187,   15875,      857607168,  859779891,  13107,      1717976832, 1717976678,
    16230,      1667644416, 1661141763, 15462,      1714822912, 1717986918, 7990,       105283328,
    103169574,  32582,      1181122304, 103169574,  3846,       1667644416, 1668481795, 31846,
    858993408,  858996531,  13107,      202120704,  202116108,  7692,       808482816,  858992688,
    7731,       912680704,  909516342,  26470,      101060352,  1715865094, 32614,      2138530560,
    1667459967, 25443,      1734566656, 1937473391, 25443,      1664490496, 1667457891, 7222,
    1717976832, 101072486,  3846,       1664490496, 2071159651, 7876670,    1717976832, 1714830950,
    26470,      858988032,  857214467,  7731,       204291840,  202116108,  7692,       858993408,
    858993459,  7731,       858993408,  858993459,  3102,       1667457792, 913009507,  13878,
    858993408,  857607198,  13107,      858993408,  202120755,  7692,       426999552,  1174801432,
    32611,      202128384,  202116108,  15372,      50397184,   806882310,  16480,      808467456,
    808464432,  15408,      1664490504, 0,          0,          0,          0,          16711680,
    1575948,    0,          0,          0,          859713566,  28211,      101058304,  1717986878,
    15206,      0,          50541342,   7731,       808466432,  858993470,  28211,      0,
    54473502,   7731,       104209408,  101064454,  3846,       0,          858993518,  506671166,
    101058304,  1717988918, 26470,      1579008,    404232222,  32280,      3158016,    808464444,
    506671920,  101058304,  907949670,  26470,      404233728,  404232216,  32280,      0,
    1802201919, 25451,      0,          858993439,  13107,      0,          858993438,  7731,
    0,          1717986875, 252067430,  0,          858993518,  2016427571, 0,          107902519,
    3846,       0,          403059486,  7731,       100925440,  101058111,  7222,       0,
    858993459,  28211,      0,          858993459,  3102,       0,          1802199907, 13878,
    0,          471610979,  25398,      0,          1717986918, 253243452,  0,          102248767,
    16163,      202127360,  201720582,  14348,      404232192,  404226072,  6168,       202114816,
    202911768,  1804,       1935396352, 0,          0,          134217728,  1667446300, 127};

// functions

void outtextxy_raster(int sx, int sy, const std::string& text) {
    if (__text_justify_vertical__ != TEXT::TOP) {
        int delta = 12 * __text_size__;
        if (__text_justify_vertical__ == TEXT::CENTER)
            delta /= 2;
        switch (__text_direction__) {
            case 1: sx += delta; break;
            case 2: sy += delta; break;
            case 3: sx -= delta; break;
            default: sy -= delta;
        }
    }
    if (__text_justify_horizontal__ != TEXT::LEFT) {
        int delta = text.length() * 8 * __text_size__;
        if (__text_justify_horizontal__ == TEXT::CENTER)
            delta /= 2;
        switch (__text_direction__) {
            case 1: sy -= delta; break;
            case 2: sx += delta; break;
            case 3: sy += delta; break;
            default: sx -= delta;
        }
    }
    const int bs = __text_size__ - 1;
    for (char ch : text) {
        auto font = (unsigned char*)(__default_font__) + ch * 12;
        int il = 12 * __text_size__, jl = 8 * __text_size__;
        for (int i = 0; i < il; i += __text_size__, font++)
            for (int j = 0, k = *font; j < jl; j += __text_size__, k /= 2)
                if (k & 1)
                    switch (__text_direction__) {
                        case 1:
                            if (bs)
                                bigpixel(sx - i, sy + j, sx - i + bs, sy + j + bs);
                            else
                                putpixel(sx - i, sy + j, __foreground_color__);
                            break;
                        case 2:
                            if (bs)
                                bigpixel(sx - j, sy - i, sx - j + bs, sy - i + bs);
                            else
                                putpixel(sx - j, sy - i, __foreground_color__);
                            break;
                        case 3:
                            if (bs)
                                bigpixel(sx + i, sy - j, sx + i + bs, sy - j + bs);
                            else
                                putpixel(sx + i, sy - j, __foreground_color__);
                            break;
                        default:
                            if (bs)
                                bigpixel(sx + j, sy + i, sx + j + bs, sy + i + bs);
                            else
                                putpixel(sx + j, sy + i, __foreground_color__);
                    }
        const float delta = 8 * __text_size__;
        switch (__text_direction__) {
            case 1: sy += delta; break;
            case 2: sx -= delta; break;
            case 3: sy -= delta; break;
            default: sx += delta;
        }
    }
}

// void outtextxy_raster(int x, int y, const std::string& text) {
//     if (y <= -12 || y >= __screen_height__)
//         return;
//     const int tl = 8 * text.length();
//     if (x <= -tl || x >= __screen_width__)
//         return;
//     const int sy = std::max(y, 0), ey = std::min(y + 12, __screen_height__);
//     unsigned char* font = (unsigned char*)__default_font__;
//     int st = std::max(0, -x / 8);
//     if (x < 0) {
//         x %= 8;
//         if (x != 0) {
//             char c = text[st];
//             for (int j = sy; j < ey; j++)
//                 for (int i = 0, v = font[c * 12 + j - y] >> -x; i < 8 + x; i++, v /= 2)
//                     if (v & 1)
//                         __screen_buffer__[j * __screen_width__ + i] = __foreground_color__;
//             x += 8; // 12x30
//             st++;
//         }
//     }
//     int et = std::min(__screen_width__ - x, tl) / 8;
//     for (; st < et; st++, x += 8) {
//         char c = text[st];
//         for (int j = sy; j < ey; j++)
//             for (int i = 0, v = font[c * 12 + j - y]; i < 8; i++, v /= 2)
//                 if (v & 1)
//                     __screen_buffer__[j * __screen_width__ + i + x] = __foreground_color__;
//     }
//     if (st < tl) {
//         const int ex = __screen_width__ - x;
//         char c = text[st];
//         for (int j = sy; j < ey; j++)
//             for (int i = 0, v = font[c * 12 + j - y]; i < ex; i++, v /= 2)
//                 if (v & 1)
//                     __screen_buffer__[j * __screen_width__ + i + x] = __foreground_color__;
//     }
// }

struct font_line {
    int8_t x1;
    int8_t y1;
    int8_t x2;
    int8_t y2;
};

struct stroke_font {
    uint8_t ascii_offset;
    uint8_t ori_cap;
    uint8_t ori_bse;
    uint8_t ori_btm;
    uint8_t height;
    uint16_t num_chars;
    uint16_t version[2];
    std::string name;
    std::string description;
    std::vector<uint8_t> widths;
    std::vector<std::vector<font_line>> lines;

    void info() {
        std::cout << "name = " << name << std::endl;
        std::cout << "version = " << version[0] << '.' << version[1] << std::endl;
        std::cout << "description = " << description << std::endl;
        std::cout << "num_chars = " << num_chars << std::endl;
        std::cout << "ascii_offset = " << (int)ascii_offset << std::endl;
        std::cout << "ori_cap = " << (int)ori_cap << std::endl;
        std::cout << "ori_bse = " << (int)ori_bse << std::endl;
        std::cout << "ori_btm = " << (int)ori_btm << std::endl;
    }
};

stroke_font __current__font__;

template <class T>
T extract(std::fstream& fin) {
    T val;
    if (!fin.read((char*)&val, sizeof(T)))
        throw std::runtime_error("File too short. Maybe corrupted.");
    return val;
}

template <class T>
void extract(std::fstream& fin, T* buffer, size_t size) {
    if (!fin.read((char*)buffer, size))
        throw std::runtime_error("File too short. Maybe corrupted.");
}

stroke_font loadfont(const char* filepath) {
    stroke_font font;
    std::fstream fin(filepath, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << filepath << " file not found" << std::endl;
        font.num_chars = 0;
        return font;
    }

    char first[8];
    if (!fin.read(first, 8))
        throw std::runtime_error("Invalid file format");

    const char* ID = "PK\b\bBGI ";
    for (int i = 0; i < 8; i++)
        if (first[i] != ID[i])
            throw std::runtime_error("Invalid file format. Wrong ID.");

    for (char c = extract<char>(fin); c != 26; c = extract<char>(fin))
        font.description += c;

    extract<uint16_t>(fin); // header_offset

    font.name = "1234";
    extract(fin, font.name.data(), 4);

    extract<uint16_t>(fin); // file_size
    font.version[0] = extract<uint8_t>(fin);
    font.version[1] = extract<uint8_t>(fin);

    auto check = extract<uint16_t>(fin);
    if (check != 1)
        throw std::runtime_error("Invalid file format. Failed check.");

    fin.seekp(0x80);
    if (extract<char>(fin) != '+')
        throw std::runtime_error("Unsupported Signature. Not a stroke font.");

    font.num_chars = extract<uint16_t>(fin);
    extract<char>(fin); // undefined
    font.ascii_offset = extract<uint8_t>(fin);

    extract<uint16_t>(fin); // stroke_offset
    extract<char>(fin);     // scan flag
    font.ori_cap = extract<uint8_t>(fin);
    font.ori_bse = extract<uint8_t>(fin);
    font.ori_btm = extract<uint8_t>(fin);

    fin.seekp(0x90);
    std::vector<uint16_t> offsets(font.num_chars);
    extract(fin, offsets.data(), 2 * offsets.size());
    font.widths.resize(font.num_chars);
    for (auto& w : font.widths)
        w = extract<uint8_t>(fin);

    font.lines.resize(font.num_chars);
    int8_t miny = 127, maxy = -128;
    for (int i = 0; i < font.num_chars; i++) {
        fin.seekp(0x90 + 3 * font.num_chars + offsets[i]);
        auto& lines = font.lines[i];
        int8_t lx = 0, ly = 0;
        auto data = extract<uint16_t>(fin);
        while ((data & 0x8000) || (data & 0x0080)) {
            int op2 = data >> 15, op1 = data & 0x80;
            int8_t y = (char)(((data >> 8) & 0x7f) << 1) >> 1, x = (char)((data & 0x7f) << 1) >> 1;
            // std::cout << (int)(x) << ',' << (int)(y) << ' ';
            miny = std::min(y, miny);
            maxy = std::max(y, maxy);
            if (op1 && op2)
                lines.push_back({lx, ly, x, y});
            lx = x;
            ly = y;
            data = extract<uint16_t>(fin);
        }
    }
    // std::cout << "min,max = " << (int)miny << ", " << (int)maxy << std::endl;
    font.height = maxy;
    fin.close();
    return font;
}

void outtextxy_stroke(float sx, float sy, const std::string& text) {
    auto& font = __current__font__;
    const float scale = __font_scales__[__text_size__];
    if (__text_justify_vertical__ != TEXT::BOTTOM) {
        float delta = font.height * scale;
        if (__text_justify_vertical__ == TEXT::CENTER)
            delta /= 2;
        switch (__text_direction__) {
            case 1: sx -= delta; break;
            case 2: sy -= delta; break;
            case 3: sx += delta; break;
            default: sy += delta;
        }
    }
    if (__text_justify_horizontal__ != TEXT::LEFT) {
        float delta = textwidth(text);
        if (__text_justify_horizontal__ == TEXT::CENTER)
            delta /= 2;
        switch (__text_direction__) {
            case 1: sy -= delta; break;
            case 2: sx += delta; break;
            case 3: sy += delta; break;
            default: sx -= delta;
        }
    }
    for (char ch : text) {
        if (ch < font.ascii_offset || ch > font.ascii_offset + font.num_chars)
            return;
        auto& lines = font.lines[ch - font.ascii_offset];
        for (auto& l : lines) {
            float x1 = l.x1 * scale, y1 = l.y1 * scale;
            float x2 = l.x2 * scale, y2 = l.y2 * scale;
            switch (__text_direction__) {
                case 1: line(sx + y1, sy + x1, sx + y2, sy + x2); break;
                case 2: line(sx - x1, sy + y1, sx - x2, sy + y2); break;
                case 3: line(sx - y1, sy - x1, sx - y2, sy - x2); break;
                default: line(sx + x1, sy - y1, sx + x2, sy - y2);
            }
        }
        const float delta = font.widths[ch - font.ascii_offset] * scale;
        switch (__text_direction__) {
            case 1: sy += delta; break;
            case 2: sx -= delta; break;
            case 3: sy -= delta; break;
            default: sx += delta;
        }
    }
}

void outtextxy(int x, int y, const std::string& text) {
    if (__font__)
        outtextxy_stroke(x, y, text);
    else
        outtextxy_raster(x, y, text);
}

int textwidth(const std::string& text) {
    if (!__font__)
        return 8 * text.length();
    auto& font = __current__font__;
    const float scale = __font_scales__[__text_size__];
    int width = 0;
    for (char ch : text)
        if (font.ascii_offset <= ch && ch < font.ascii_offset + font.num_chars)
            width += font.widths[ch - font.ascii_offset] * scale;
    return width;
}

int textheight(const std::string& text) {
    if (!__font__)
        return 12;
    std::ignore = text;
    return __current__font__.height * __font_scales__[__text_size__];
}

void settextstyle(int font, int direction, int charsize) {
    font = std::clamp(font, 0, 10);
    if (__font__ != font) {
        __font__ = font;
        if (__font__) {
            __current__font__ = loadfont(__fontfiles__[__font__]);
            if (__current__font__.num_chars == 0)
                __font__ = 0;
            // __current__font__.info();
        }
    }
    __text_direction__ = direction;
    __text_size__ = std::clamp(charsize, 0, 10);
    if (!__font__ && !__text_size__)
        __text_size__ = 1;
}

void settextjustify(int horizontal, int vertical) {
    __text_justify_horizontal__ = horizontal;
    __text_justify_vertical__ = vertical;
}

} // namespace lfbg