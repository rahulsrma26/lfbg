#include "lfbg/graphics.h"

namespace lfbg {

extern int __screen_width__, __screen_height__;
extern std::vector<color> __screen_buffer__;
extern color __foreground_color__;

color __fill_color__ = COLOR::WHITE;
uint64_t __fill_patterns__[20] = {0,
0xFFFFFFFFFFFFFFFF,
0xFFFFFFFF00000000,
0x0102040810204080,
0xC3870F1E3C78F0E1,
0xE1F0783C1E0F87C3,
0xD269B45A2D964BA5,
0xFF888888FF888888,
0x8142241818244281,
0xAA55AA55AA55AA55,
0x8000080080000800,
0x8800220088002200,
0x3333CCCC3333CCCC,
0xF0F0F0F00F0F0F0F,
0x0010284428100000,
0xFF7E3C18183C7EFF,
0x0010107C10100000,
0x0042241818244200,
0x8040201008040201,
0x331B0F1B331B0F00};
uint64_t __fill_pattern__ = __fill_patterns__[1];

void setfillstyle(int style, color c) {
    __fill_pattern__ = __fill_patterns__[std::clamp(style, 0, 19)];
    __fill_color__ = c;
}

void setfillpattern(uint64_t pattern8x8){
    __fill_pattern__ = pattern8x8;
}

uint64_t getfillpattern(){
    return __fill_pattern__;
}

color getfillcolor(){
    return __fill_color__;
}

void fline(int x1, int x2, int y) {
    if (x1 > x2)
        std::swap(x1, x2);
    if (0 <= y && y < __screen_height__ && x2 > 0 && x1 < __screen_width__) {
        if (x1 < 0)
            x1 = 0;
        if (x2 >= __screen_width__)
            x2 = __screen_width__ - 1;
        for (; x1 <= x2; x1++)
            if (((__fill_pattern__ >> ((y & 7) << 3)) >> (x1 & 7)) & 1)
                __screen_buffer__[y * __screen_width__ + x1] = __fill_color__;
    }
}

void hline(int x1, int x2, int y) {
    if (x1 > x2)
        std::swap(x1, x2);
    if (0 <= y && y < __screen_height__ && x2 > 0 && x1 < __screen_width__) {
        if (x1 < 0)
            x1 = 0;
        if (x2 >= __screen_width__)
            x2 = __screen_width__ - 1;
        for (; x1 <= x2; x1++)
            __screen_buffer__[y * __screen_width__ + x1] = __foreground_color__;
    }
}

void vline(int y1, int y2, int x) {
    if (y1 > y2)
        std::swap(y1, y2);
    if (0 <= x && x < __screen_width__ && y2 > 0 && y1 < __screen_height__) {
        if (y1 < 0)
            y1 = 0;
        if (y2 >= __screen_height__)
            y2 = __screen_height__ - 1;
        for (; y1 <= y2; y1++)
            __screen_buffer__[y1 * __screen_width__ + x] = __foreground_color__;
    }
}

void rectangle(int left, int top, int right, int bottom) {
    hline(left, right, top);
    hline(left, right, bottom);
    vline(top, bottom, left);
    vline(top, bottom, right);
}

void bar(int left, int top, int right, int bottom) {
    if (left > right)
        std::swap(left, right);
    if (top > bottom)
        std::swap(top, bottom);
    if (right < 0 || left >= __screen_width__ || bottom < 0 || top >= __screen_height__)
        return;
    if (left < 0)
        left = 0;
    if (right >= __screen_width__)
        right = __screen_width__ - 1;
    if (top < 0)
        top = 0;
    if (bottom >= __screen_height__)
        bottom = __screen_height__ - 1;
    for (; top <= bottom; top++)
        fline(left, right, top);
}

void bigpixel(int left, int top, int right, int bottom) {
    if (left > right)
        std::swap(left, right);
    if (top > bottom)
        std::swap(top, bottom);
    if (right < 0 || left >= __screen_width__ || bottom < 0 || top >= __screen_height__)
        return;
    if (left < 0)
        left = 0;
    if (right >= __screen_width__)
        right = __screen_width__ - 1;
    if (top < 0)
        top = 0;
    if (bottom >= __screen_height__)
        bottom = __screen_height__ - 1;
    auto begin = __screen_buffer__.begin() + left;
    auto end = __screen_buffer__.begin() + right + 1;
    for (int offset = top * __screen_width__; top <= bottom; top++, offset += __screen_width__)
        std::fill(begin + offset, end + offset, __foreground_color__);
}

void floodfill(int x, int y, color border) {
    if (x < 0 || y < 0 || x >= __screen_width__ || y >= __screen_height__)
        return;
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        for (int i = q.size(); i; i--) {
            auto [px, py] = q.front();
            q.pop();
            if (0 <= px && px < __screen_width__ && 0 <= py && py < __screen_height__ &&
                __screen_buffer__[py * __screen_width__ + px] != border &&
                __screen_buffer__[py * __screen_width__ + px] != __fill_color__) {
                __screen_buffer__[py * __screen_width__ + px] = __fill_color__;
                q.push({px + 1, py});
                q.push({px - 1, py});
                q.push({px, py + 1});
                q.push({px, py - 1});
            }
        }
    }
}

constexpr int COHEN_SUTHERLAND_INSIDE = 0b0000;
constexpr int COHEN_SUTHERLAND_LEFT = 0b0001;
constexpr int COHEN_SUTHERLAND_RIGHT = 0b0010;
constexpr int COHEN_SUTHERLAND_BOTTOM = 0b0100;
constexpr int COHEN_SUTHERLAND_TOP = 0b1000;

int cohen_sutherland_code(int x, int y) {
    int code = COHEN_SUTHERLAND_INSIDE;
    if (x < 0)
        code |= COHEN_SUTHERLAND_LEFT;
    else if (x >= __screen_width__)
        code |= COHEN_SUTHERLAND_RIGHT;
    if (y < 0)
        code |= COHEN_SUTHERLAND_BOTTOM;
    else if (y >= __screen_height__)
        code |= COHEN_SUTHERLAND_TOP;
    return code;
}

bool cohen_sutherland_clip(int& x1, int& y1, int& x2, int& y2) {
    int c1 = cohen_sutherland_code(x1, y1);
    int c2 = cohen_sutherland_code(x2, y2);
    bool accept = false;
    while (true) {
        if (c1 == 0 && c2 == 0) { // If both endpoints lie within rectangle
            accept = true;
            break;
        } else if (c1 & c2) { // If both endpoints are outside rectangle, in same region
            break;
        } else { // Some segment of line lies within the rectangle
            double x{0}, y{0};
            // At least one endpoint is outside the
            // rectangle, pick it.
            int co = c1 != 0 ? c1 : c2;
            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (co & COHEN_SUTHERLAND_TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (__screen_height__ - 1 - y1) / (y2 - y1);
                y = __screen_height__ - 1;
            } else if (co & COHEN_SUTHERLAND_BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (0 - y1) / (y2 - y1);
                y = 0;
            } else if (co & COHEN_SUTHERLAND_RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (__screen_width__ - 1 - x1) / (x2 - x1);
                x = __screen_width__ - 1;
            } else if (co & COHEN_SUTHERLAND_LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (0 - x1) / (x2 - x1);
                x = 0;
            }
            // Now intersection point x,y is found. We replace point outside rectangle by
            // intersection point
            if (co == c1) {
                x1 = x;
                y1 = y;
                c1 = cohen_sutherland_code(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                c2 = cohen_sutherland_code(x2, y2);
            }
        }
    }
    return accept;
}

void line(int x1, int y1, int x2, int y2) {
    if (!cohen_sutherland_clip(x1, y1, x2, y2))
        return;
    int x, y, dx, dy, incx, incy, balance;

    if (x2 >= x1) {
        dx = x2 - x1;
        incx = 1;
    } else {
        dx = x1 - x2;
        incx = -1;
    }

    if (y2 >= y1) {
        dy = y2 - y1;
        incy = 1;
    } else {
        dy = y1 - y2;
        incy = -1;
    }

    x = x1;
    y = y1;

    if (dx >= dy) {
        dy <<= 1;
        balance = dy - dx;
        dx <<= 1;

        while (x != x2) {
            __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
            if (balance >= 0) {
                y += incy;
                balance -= dx;
            }
            balance += dy;
            x += incx;
        }
        __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
    } else {
        dx <<= 1;
        balance = dx - dy;
        dy <<= 1;

        while (y != y2) {
            __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
            if (balance >= 0) {
                x += incx;
                balance -= dy;
            }
            balance += dx;
            y += incy;
        }
        __screen_buffer__[y * __screen_width__ + x] = __foreground_color__;
    }
}

inline void circle_symmetric_plot(int xc, int yc, int x, int y) {
    putpixel(x + xc, y + yc, __foreground_color__);
    putpixel(x + xc, -y + yc, __foreground_color__);
    putpixel(-x + xc, -y + yc, __foreground_color__);
    putpixel(-x + xc, y + yc, __foreground_color__);
    putpixel(y + xc, x + yc, __foreground_color__);
    putpixel(y + xc, -x + yc, __foreground_color__);
    putpixel(-y + xc, -x + yc, __foreground_color__);
    putpixel(-y + xc, x + yc, __foreground_color__);
}

void circle(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - (2 * r);
    circle_symmetric_plot(xc, yc, x, y);
    while (x < y) {
        if (d <= 0) {
            d = d + (4 * x) + 6;
        } else {
            d = d + (4 * x) - (4 * y) + 10;
            y = y - 1;
        }
        x = x + 1;
        circle_symmetric_plot(xc, yc, x, y);
    }
}

inline void arc_symmetric_plot(int xc, int yc, int x, int y, int start, int end) {
    int angle = 180 * std::atan2(y, x) / 3.141592653589;
    if (90 - angle >= start && 90 - angle <= end)
        putpixel(xc + y, yc - x, __foreground_color__);
    if (angle >= start && angle <= end)
        putpixel(xc + x, yc - y, __foreground_color__);
    if (180 - angle >= start && 180 - angle <= end)
        putpixel(xc - x, yc - y, __foreground_color__);
    if (angle + 90 >= start && angle + 90 <= end)
        putpixel(xc - y, yc - x, __foreground_color__);
    if (270 - angle >= start && 270 - angle <= end)
        putpixel(xc - y, yc + x, __foreground_color__);
    if (angle + 180 >= start && angle + 180 <= end)
        putpixel(xc - x, yc + y, __foreground_color__);
    if (360 - angle >= start && 360 - angle <= end)
        putpixel(xc + x, yc + y, __foreground_color__);
    if (angle + 270 >= start && angle + 270 <= end)
        putpixel(xc + y, yc + x, __foreground_color__);
}

void arc(int xc, int yc, int start, int end, int r) {
    if (end < start)
        end += 360;
    int x = 0, y = r, d = 3 - (2 * r);
    arc_symmetric_plot(xc, yc, x, y, start, end);
    while (x < y) {
        if (d <= 0) {
            d = d + (4 * x) + 6;
        } else {
            d = d + (4 * x) - (4 * y) + 10;
            y = y - 1;
        }
        x = x + 1;
        arc_symmetric_plot(xc, yc, x, y, start, end);
    }
}

void fillcircle(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - (2 * r);
    fline(xc - r, xc + r, yc);
    while (x < y) {
        if (d <= 0) {
            d = d + (4 * x) + 6;
        } else {
            d = d + (4 * x) - (4 * y) + 10;
            y = y - 1;
            fline(xc - x, xc + x, yc + y);
            fline(xc - x, xc + x, yc - y);
        }
        x = x + 1;
        fline(xc - y, xc + y, yc - x);
        fline(xc - y, xc + y, yc + x);
    }
}

inline void ellipse_symmetric_plot(int xc, int yc, int x, int y, char flag) {
    if (flag)
        std::swap(x, y);
    putpixel(x + xc, y + yc, __foreground_color__);
    putpixel(-x + xc, y + yc, __foreground_color__);
    putpixel(-x + xc, -y + yc, __foreground_color__);
    putpixel(x + xc, -y + yc, __foreground_color__);
}

void ellipse_helper(int cx, int cy, int xr, int yr, char flag) {
    int xr22 = 2 * xr * xr, yr22 = 2 * yr * yr;
    int x = xr, y = 0;
    int dx = yr * yr * (1 - 2 * xr), dy = xr * xr;
    int err = 0, sx = yr22 * xr, sy = 0;
    while (sx >= sy) {
        ellipse_symmetric_plot(cx, cy, x, y, flag);
        y++;
        sy += xr22;
        err += dy;
        dy += xr22;
        if (2 * err + dx > 0) {
            x--;
            sx -= yr22;
            err += dx;
            dx += yr22;
        }
    }
}

void ellipse(int cx, int cy, int xr, int yr) {
    ellipse_helper(cx, cy, xr, yr, 0);
    ellipse_helper(cx, cy, yr, xr, 1);
}

void ellipse_fill_middle(int cx, int cy, int xr, int yr) {
    int xr22 = 2 * xr * xr, yr22 = 2 * yr * yr;
    int x = xr, y = 0;
    int dx = yr * yr * (1 - 2 * xr), dy = xr * xr;
    int err = 0, sx = yr22 * xr, sy = 0;
    while (sx >= sy) {
        fline(cx - x, cx + x, cy + y);
        fline(cx - x, cx + x, cy - y);
        y++;
        sy += xr22;
        err += dy;
        dy += xr22;
        if (2 * err + dx > 0) {
            x--;
            sx -= yr22;
            err += dx;
            dx += yr22;
        }
    }
}

void ellipse_fill_outer(int cx, int cy, int xr, int yr) {
    int xr22 = 2 * xr * xr, yr22 = 2 * yr * yr;
    int x = xr, y = 0;
    int dx = yr * yr * (1 - 2 * xr), dy = xr * xr;
    int err = 0, sx = yr22 * xr, sy = 0;
    while (sx >= sy) {
        y++;
        sy += xr22;
        err += dy;
        dy += xr22;
        if (2 * err + dx > 0) {
            fline(cx - y, cx + y, cy + x);
            fline(cx - y, cx + y, cy - x);
            x--;
            sx -= yr22;
            err += dx;
            dx += yr22;
        }
    }
}

void fillellipse(int cx, int cy, int xr, int yr) {
    ellipse_fill_middle(cx, cy, xr, yr);
    ellipse_fill_outer(cx, cy, yr, xr);
}

// Fill a triangle - slope method
// Original Author: Adafruit Industries
void filltriangle(int x0, int y0, int x1, int y1, int x2, int y2){
    int a, b, y, last;
  	// Sort coordinates by Y order (y2 >= y1 >= y0)
  	if (y0 > y1) { std::swap(y0, y1); std::swap(x0, x1); }
  	if (y1 > y2) { std::swap(y2, y1); std::swap(x2, x1); }
  	if (y0 > y1) { std::swap(y0, y1); std::swap(x0, x1); }

  	if(y0 == y2) { // All on same line case
    	a = b = x0;
    	if(x1 < a)      a = x1;
    	else if(x1 > b) b = x1;
    	if(x2 < a)      a = x2;
    	else if(x2 > b) b = x2;
        fline(a, b, y0);
        return;
    }

    int
        dx01 = x1 - x0,
        dy01 = y1 - y0,
        dx02 = x2 - x0,
        dy02 = y2 - y0,
        dx12 = x2 - x1,
        dy12 = y2 - y1;
    int sa = 0, sb = 0;

    // For upper part of triangle, find scanline crossings for segment
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y
    // is included here (and second loop will be skipped, avoiding a /
    // error there), otherwise scanline y1 is skipped here and handle
    // in the second loop...which also avoids a /0 error here if y0=y
    // (flat-topped triangle)
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        // longhand a = x0 + (x1 - x0) * (y - y0) / (y1 - y0)
        //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
        fline(a, b, y);
    }

    // For lower part of triangle, find scanline crossings for segment
    // 0-2 and 1-2.  This loop is skipped if y1=y2
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        // longhand a = x1 + (x2 - x1) * (y - y1) / (y2 - y1)
        //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
        fline(a, b, y);
    }
}

} // namespace lfbg