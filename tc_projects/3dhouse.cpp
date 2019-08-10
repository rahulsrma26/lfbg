#include <stdlib.h>
#include <string>
#include "lfbg/graphics.h"
using namespace std;
using namespace lfbg;

float camra_a = 0, camra_b = 0, camra_x = 0, camra_y = -100, camra_z = 50;

int d3l(float x1, float y1, int z1, float x2, float y2, int z2, float& x11, float& y11, float& x21,
        float& y21) {
    x1 -= camra_x;
    y1 -= camra_y;
    z1 -= camra_z;
    x2 -= camra_x;
    y2 -= camra_y;
    z2 -= camra_z;
    float tmp_x = x1 * cos(camra_a) + z1 * sin(camra_a);
    float tmp_z = z1 * cos(camra_a) - x1 * sin(camra_a);
    z1 = tmp_z;
    x1 = tmp_x;
    tmp_x = x2 * cos(camra_a) + z2 * sin(camra_a);
    tmp_z = z2 * cos(camra_a) - x2 * sin(camra_a);
    z2 = tmp_z;
    x2 = tmp_x;
    float tmp_y = y1 * cos(camra_b) + z1 * sin(camra_b);
    tmp_z = z1 * cos(camra_b) - y1 * sin(camra_b);
    z1 = tmp_z;
    y1 = tmp_y;
    tmp_y = y2 * cos(camra_b) + z2 * sin(camra_b);
    tmp_z = z2 * cos(camra_b) - y2 * sin(camra_b);
    z2 = tmp_z;
    y2 = tmp_y;
    if (z1 < 50 && z2 < 50)
        return 0;
    if (z1 < 50) {
        tmp_x = ((z2 - 50) * x1 + (50 - z1) * x2) / (z2 - z1);
        tmp_y = ((z2 - 50) * y1 + (50 - z1) * y2) / (z2 - z1);
        x1 = tmp_x;
        y1 = tmp_y;
        z1 = 50;
    }
    if (z2 < 50) {
        tmp_x = ((z1 - 50) * x2 + (50 - z2) * x1) / (z1 - z2);
        tmp_y = ((z1 - 50) * y2 + (50 - z2) * y1) / (z1 - z2);
        x2 = tmp_x;
        y2 = tmp_y;
        z2 = 50;
    }
    {
        x11 = ((225 * x1) / z1) + 320;
        y11 = ((225 * y1) / z1) + 200;
        x21 = ((225 * x2) / z2) + 320;
        y21 = ((225 * y2) / z2) + 200;
    }
    return 1;
}

void d3l(float x1, float y1, int z1, float x2, float y2, int z2) {
    float x11, y11, x21, y21;
    if (d3l(x1, y1, z1, x2, y2, z2, x11, y11, x21, y21))
        line(x11, y11, x21, y21);
}

void fillquad(int x1, int y1, int x2, int y2, int x4, int y4, int x3, int y3) {
    // setfillstyle(1, getcolor());
    // filltriangle(x1, y1, x2, y2, x4, y4);
    // filltriangle(x1, y1, x4, y4, x3, y3);
    int i, loop;
    float x1_inc, y1_inc, x2_inc, y2_inc, X1, Y1, X2, Y2, dx, dy;
    loop = abs(x2 - x1);
    if (abs(y2 - y1) > loop)
        loop = abs(y2 - y1);
    else if (abs(y4 - y3) > loop)
        loop = abs(y4 - y3);
    else if (abs(x4 - x3) > loop)
        loop = abs(x4 - x3);
    dx = x2 - x1;
    dy = y2 - y1;
    x1_inc = (float)dx / loop;
    y1_inc = (float)dy / loop;
    dx = x4 - x3;
    dy = y4 - y3;
    x2_inc = (float)dx / loop;
    y2_inc = (float)dy / loop;
    X1 = x1;
    Y1 = y1;
    X2 = x3;
    Y2 = y3;
    line(round(X1), round(Y1), round(X2), round(Y2));
    for (i = 1; i <= loop; i++) {
        X1 += x1_inc;
        Y1 += y1_inc;
        X2 += x2_inc;
        Y2 += y2_inc;
        line(round(X1), round(Y1), round(X2), round(Y2));
    }
}

class plane {
public:
    float px[4], py[4], pz[4];
    plane() {}
    plane(float a1, float b1, float c1, float a2, float b2, float c2, float a3, float b3, float c3,
          float a4, float b4, float c4) {
        px[0] = a1;
        px[1] = a2;
        px[2] = a3;
        px[3] = a4;
        py[0] = b1;
        py[1] = b2;
        py[2] = b3;
        py[3] = b4;
        pz[0] = c1;
        pz[1] = c2;
        pz[2] = c3;
        pz[3] = c4;
    }
    void get(float a1, float b1, float c1, float a2, float b2, float c2, float a3, float b3,
             float c3, float a4, float b4, float c4) {
        px[0] = a1;
        px[1] = a2;
        px[2] = a3;
        px[3] = a4;
        py[0] = b1;
        py[1] = b2;
        py[2] = b3;
        py[3] = b4;
        pz[0] = c1;
        pz[1] = c2;
        pz[2] = c3;
        pz[3] = c4;
    }
    void put() {
        d3l(px[0], py[0], pz[0], px[1], py[1], pz[1]);
        d3l(px[0], py[0], pz[0], px[3], py[3], pz[3]);
        d3l(px[2], py[2], pz[2], px[1], py[1], pz[1]);
        d3l(px[2], py[2], pz[2], px[3], py[3], pz[3]);
    }
    void fill() {
        float px1, px2, py1, py2, px3, py3, px4, py4;
        if (d3l(px[0], py[0], pz[0], px[1], py[1], pz[1], px1, py1, px2, py2) &&
            d3l(px[2], py[2], pz[2], px[3], py[3], pz[3], px3, py3, px4, py4))
            if ((px1 >= 0 && px1 < 640 && py1 >= 0 && py1 < 400) ||
                (px3 >= 0 && px3 < 640 && py3 >= 0 && py3 < 400))
                // if((px1>=0&&px1<640&&py1>=0&&py1<400)&&(px2>=0&&px2<640&&py2>=0&&py2<400)&&(px3>=0&&px3<640&&py3>=0&&py3<400)&&(px4>=0&&px4<640&&py4>=0&&py4<400))
                fillquad(px1, py1, px2, py2, px3, py3, px4, py4);
    }
    void forward(float v) {
        for (int i = 0; i < 4; i++)
            pz[i] += v;
    }
    void backward(float v) {
        for (int i = 0; i < 4; i++)
            pz[i] -= v;
    }
    void turnl(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_x = (px[i] * 0.99875) + (pz[i] * .05);
            float tmp_z = (pz[i] * 0.99875) - (px[i] * .05);
            px[i] = tmp_x;
            pz[i] = tmp_z;
        }
    }
    void turnr(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_x = (px[i] * 0.99875) - (pz[i] * .05);
            float tmp_z = (pz[i] * 0.99875) + (px[i] * .05);
            px[i] = tmp_x;
            pz[i] = tmp_z;
        }
    }
    void turnu(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_y = (py[i] * 0.99875) + (pz[i] * .05);
            float tmp_z = (pz[i] * 0.99875) - (py[i] * .05);
            py[i] = tmp_y;
            pz[i] = tmp_z;
        }
    }
    void turnd(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_y = (py[i] * 0.99875) - (pz[i] * .05);
            float tmp_z = (pz[i] * 0.99875) + (py[i] * .05);
            py[i] = tmp_y;
            pz[i] = tmp_z;
        }
    }
    void rotc(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_y = (py[i] * 0.99875) + (px[i] * .05);
            float tmp_x = (px[i] * 0.99875) - (py[i] * .05);
            py[i] = tmp_y;
            px[i] = tmp_x;
        }
    }
    void rota(void) {
        for (int i = 0; i < 4; i++) {
            float tmp_y = (py[i] * 0.99875) - (px[i] * .05);
            float tmp_x = (px[i] * 0.99875) + (py[i] * .05);
            py[i] = tmp_y;
            px[i] = tmp_x;
        }
    }
    void right(float v) {
        for (int i = 0; i < 4; i++)
            px[i] += v;
    }
    void left(float v) {
        for (int i = 0; i < 4; i++)
            px[i] -= v;
    }
    void lift(float v) {
        for (int i = 0; i < 4; i++)
            py[i] += v;
    }
    void duck(float v) {
        for (int i = 0; i < 4; i++)
            py[i] -= v;
    }
};

class cube {
public:
    float px[8], py[8], pz[8], x[8], y[8], z[8];
    cube() {}
    cube(float a, float b, float c, float d, float e, float f) {
        px[0] = px[3] = px[7] = px[4] = a;
        px[1] = px[2] = px[6] = px[5] = d;
        py[0] = py[1] = py[5] = py[4] = b;
        py[3] = py[2] = py[6] = py[7] = e;
        pz[0] = pz[1] = pz[2] = pz[3] = c;
        pz[4] = pz[5] = pz[6] = pz[7] = f;
    }
    void get(float a, float b, float c, float d, float e, float f) {
        px[0] = px[3] = px[7] = px[4] = a;
        px[1] = px[2] = px[6] = px[5] = d;
        py[0] = py[1] = py[5] = py[4] = b;
        py[3] = py[2] = py[6] = py[7] = e;
        pz[0] = pz[1] = pz[2] = pz[3] = c;
        pz[4] = pz[5] = pz[6] = pz[7] = f;
    }
    void put() {
        d3l(px[0], py[0], pz[0], px[1], py[1], pz[1]);
        d3l(px[0], py[0], pz[0], px[3], py[3], pz[3]);
        d3l(px[2], py[2], pz[2], px[1], py[1], pz[1]);
        d3l(px[2], py[2], pz[2], px[3], py[3], pz[3]);
        d3l(px[4], py[4], pz[4], px[5], py[5], pz[5]);
        d3l(px[4], py[4], pz[4], px[7], py[7], pz[7]);
        d3l(px[6], py[6], pz[6], px[5], py[5], pz[5]);
        d3l(px[6], py[6], pz[6], px[7], py[7], pz[7]);
        d3l(px[0], py[0], pz[0], px[4], py[4], pz[4]);
        d3l(px[1], py[1], pz[1], px[5], py[5], pz[5]);
        d3l(px[2], py[2], pz[2], px[6], py[6], pz[6]);
        d3l(px[3], py[3], pz[3], px[7], py[7], pz[7]);
    }
    void forward(float v) {
        for (int i = 0; i < 8; i++)
            pz[i] += v;
    }
    void backward(float v) {
        for (int i = 0; i < 8; i++)
            pz[i] -= v;
    }
    void turnl(void) {
        for (int i = 0; i < 8; i++) {
            x[i] = (px[i] * 0.99875) + (pz[i] * .05);
            z[i] = (pz[i] * 0.99875) - (px[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            px[i] = x[i];
            pz[i] = z[i];
        }
    }
    void turnr(void) {
        for (int i = 0; i < 8; i++) {
            x[i] = (px[i] * 0.99875) - (pz[i] * .05);
            z[i] = (pz[i] * 0.99875) + (px[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            px[i] = x[i];
            pz[i] = z[i];
        }
    }
    void turnu(void) {
        for (int i = 0; i < 8; i++) {
            y[i] = (py[i] * 0.99875) + (pz[i] * .05);
            z[i] = (pz[i] * 0.99875) - (py[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            py[i] = y[i];
            pz[i] = z[i];
        }
    }
    void turnd(void) {
        for (int i = 0; i < 8; i++) {
            y[i] = (py[i] * 0.99875) - (pz[i] * .05);
            z[i] = (pz[i] * 0.99875) + (py[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            py[i] = y[i];
            pz[i] = z[i];
        }
    }
    void rotc(void) {
        for (int i = 0; i < 8; i++) {
            y[i] = (py[i] * 0.99875) + (px[i] * .05);
            x[i] = (px[i] * 0.99875) - (py[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            py[i] = y[i];
            px[i] = x[i];
        }
    }
    void rota(void) {
        for (int i = 0; i < 8; i++) {
            y[i] = (py[i] * 0.99875) - (px[i] * .05);
            x[i] = (px[i] * 0.99875) + (py[i] * .05);
        }
        for (int i = 0; i < 8; i++) {
            py[i] = y[i];
            px[i] = x[i];
        }
    }
    void right(float v) {
        for (int i = 0; i < 8; i++)
            px[i] += v;
    }
    void left(float v) {
        for (int i = 0; i < 8; i++)
            px[i] -= v;
    }
    void lift(float v) {
        for (int i = 0; i < 8; i++)
            py[i] += v;
    }
    void duck(float v) {
        for (int i = 0; i < 8; i++)
            py[i] -= v;
    }
};

void set8bitpalette() {
    int r, g, b, colorindex = 0;
    for (r = 0; r < 64; r += 9)
        for (g = 0; g < 64; g += 9)
            for (b = 0; b < 64; b += 21) {
                set_palette(colorindex, rgb2color(r * 4, g * 4, b * 4));
                colorindex++;
            }
}

cube cu[59];
plane su[138];
int nosu = 120, nocu = 59, contf = 0;

int main(int argc, char* argv[]) {
    int i, j, k = 0, l = 0, x, y;
    for (i = -1500; i < 1500; i += 1000)
        for (j = 1500; j < 4500; j += 1000) {
            cu[k].get(i, -600, j, i + 1000, -800, j + 1000);
            k++;
        }
    for (i = -1500; i < 1500; i += 500)
        for (j = 1500; j < 4500; j += 500) {
            cu[k].get(i, 700, j, i + 500, 800, j + 500);
            k++;
        }
    for (i = -1500; i < 1500; i += 1000)
        for (j = 1500; j < 4500; j += 500) {
            if (l % 2 == 0)
                su[102 + l++].get(i, 800, j, i + 500, 800, j, i + 500, 800, j + 500, i, 800,
                                  j + 500);
            else
                su[102 + l++].get(i + 500, 800, j, i + 1000, 800, j, i + 1000, 800, j + 500,
                                  i + 500, 800, j + 500);
        }
    for (j = 1500; j < 4500; j += 1000) {
        cu[k].get(-1500, -600, j, -1200, 700, j + 333);
        cu[k].forward((j - 1500) / 3);
        k++;
    }
    for (j = 1500; j < 4500; j += 1000) {
        cu[k].get(1200, -600, j, 1500, 700, j + 333);
        cu[k].forward((j - 1500) / 3);
        k++;
    }
    cu[k].get(-1500, -3200, 1500, 0, -3100, 4500);
    k++;
    cu[51].py[0] += 800;
    cu[51].py[3] += 800;
    cu[51].py[4] += 800;
    cu[51].py[7] += 800;
    cu[k].get(0, -3200, 1500, 1500, -3100, 4500);
    k++;
    cu[52].py[1] += 800;
    cu[52].py[2] += 800;
    cu[52].py[5] += 800;
    cu[52].py[6] += 800;
    for (j = 1500; j < 4500; j += 1000) {
        cu[k].get(-1500, -2400, j, -1200, -800, j + 333);
        cu[k].py[1] -= 160;
        cu[k].py[5] -= 160;
        cu[k].forward((j - 1500) / 3);
        k++;
    }
    for (j = 1500; j < 4500; j += 1000) {
        cu[k].get(1200, -2400, j, 1500, -800, j + 333);
        cu[k].py[0] -= 160;
        cu[k].py[4] -= 160;
        cu[k].forward((j - 1500) / 3);
        k++;
    }
    k = 0;
    for (i = -2500; i < 2500; i += 250) {
        su[k].get(i, 200, 6000, i + 100, 200, 6000, i + 100, 800, 6000, i, 800, 6000);
        k++;
    }
    for (i = 0; i < 6000; i += 250) {
        su[k].get(-2500, 200, i, -2500, 200, i + 100, -2500, 800, i + 100, -2500, 800, i);
        k++;
    }
    for (i = 0; i < 6000; i += 250) {
        su[k].get(2500, 200, i, 2500, 200, i + 100, 2500, 800, i + 100, 2500, 800, i);
        k++;
    }
    for (i = -2500; i < -500; i += 250) {
        su[k].get(i, 200, 0, i + 100, 200, 0, i + 100, 800, 0, i, 800, 0);
        k++;
    }
    for (i = 500; i < 2500; i += 250) {
        su[k].get(i, 200, 0, i + 100, 200, 0, i + 100, 800, 0, i, 800, 0);
        k++;
    }
    su[k].get(-500, 0, 0, 0, 0, 0, 0, 800, 0, -500, 800, 0);
    k++;
    su[k].get(500, 0, 0, 0, 0, 0, 0, 800, 0, 500, 800, 0);
    k++;
    for (i = 800; i > 0; i -= 100) {
        su[k].get(500, i - 50, 0, 0, i, 0, 0, i, 0, 500, i - 50, 0);
        k++;
    }
    for (i = 800; i > 0; i -= 100) {
        su[k].get(0, i, 0, -500, i - 50, 0, -500, i - 50, 0, 0, i, 0);
        k++;
    }

    constexpr int w = 640, h = 480;
    float multiplier = 0;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(w, h, multiplier, RenderType::Retro, 2);
    enable_palette();
    set8bitpalette();
    set_raw_cursor_pos_callback();
    glfwSetInputMode(get_window_handle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    int scaler = get_window_size().second;
    set_cursor_pos(scaler/2, scaler/2);

    while (!closed()) {
        if (camra_z > 1500 && camra_z < 4500 && camra_x > -1500 && camra_x < 1500) {
            for (i = 0; i < 6; i++)
                if (cu[15 + i].py[0] > (600 - (i)*100))
                    cu[15 + i].duck(5);
            for (i = 0; i < 6; i++)
                if (cu[21 + i].py[0] > (5 - i) * -100)
                    cu[21 + i].duck(5);
            x = (camra_x + 1500) / 500;
            y = (camra_z - 1500) / 500;
            camra_y = cu[9 + x * 6 + y].py[0] - 800;
        } else {
            for (i = 0; i < 12; i++)
                if (cu[15 + i].py[0] < 700)
                    cu[15 + i].lift(5);
            if (camra_y < -100)
                camra_y += 50;
            else if (camra_y > -100)
                camra_y -= 50;
        }
        auto [mousex, mousey] = get_cursor_pos();
        camra_a = camra_a + (scaler/2 - mousex) / scaler;
        camra_b = camra_b + (scaler/2 - mousey) / scaler;
        if (camra_b > 1.57)
            camra_b = 1.57;
        if (camra_b < -1.57)
            camra_b = -1.57;
        set_cursor_pos(scaler/2, scaler/2);
        if (is_key_pressed(GLFW_KEY_W)) { // 72
            camra_x -= 50 * sin(camra_a);
            camra_z += 50 * cos(camra_a);
        }
        if (is_key_pressed(GLFW_KEY_S)) { // 80
            camra_x += 50 * sin(camra_a);
            camra_z -= 50 * cos(camra_a);
        }
        if (is_key_pressed(GLFW_KEY_D)) { // 77
            camra_x += 50 * cos(camra_a);
            camra_z += 50 * sin(camra_a);
        }
        if (is_key_pressed(GLFW_KEY_A)) { // 75
            camra_x -= 50 * cos(camra_a);
            camra_z -= 50 * sin(camra_a);
        }
        if (is_key_pressed(GLFW_KEY_Q)) { // -111
            camra_y += 50;
        }
        if (is_key_pressed(GLFW_KEY_E)) { // -115
            camra_y -= 50;
        }
        setcolor(110);
        for (i = 0; i < 68; i++)
            su[i].fill();
        setcolor(165);
        for (i = 45; i < 51; i++)
            cu[i].put();
        setcolor(53);
        for (i = 9; i < 45; i++)
            cu[i].put();
        setcolor(146);
        for (i = 0; i < 9; i++)
            cu[i].put();
        setcolor(136);
        for (i = 51; i < 53; i++)
            cu[i].put();
        setcolor(166);
        for (i = 53; i < 59; i++)
            cu[i].put();
        setcolor(191);
        for (i = 68; i < 84; i++)
            su[i].fill();
        setcolor(156);
        for (i = 84; i < 102; i++)
            su[i].put();
        // setcolor(156)  ; for(i=102;i<120;i++)su[i].fill();
        bitblt();
        cleardevice();
    }
    closegraph();
}
