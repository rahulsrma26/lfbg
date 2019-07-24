#include <stdlib.h>
#include <string>
#include <deque>
#include "lfbg/graphics.h"

using namespace std;
using namespace lfbg;
constexpr int width = 32, height = 20;

struct snake {
    deque<point2d<int>> body;
    snake() { body.push_front({height / 2, width / 2}); }
    point2d<int> next(point2d<int> d) {
        return {(body.front().x + d.x + width) % width, (body.front().y + d.y + height) % height};
    }
    bool hit(point2d<int> point) {
        for (auto& p : body)
            if (p.x == point.x && p.y == point.y)
                return true;
        return false;
    }
    point2d<int> mouse() {
        point2d<int> m{rand() % width, rand() % height};
        while (hit(m))
            m = {rand() % width, rand() % height};
        return m;
    }
};

int main(int argc, char* argv[]) {

    float multiplier = 10;
    if (argc > 1)
        multiplier = std::stof(argv[1]);

    initgraph(width, height, multiplier, RenderType::Retro, 1);
    snake s;
    auto dir = point2d<int>{-1, 0};
    auto mouse = s.mouse();
    bool game_over = false;
    int frame = 0, speed = 10, eaten = 0;
    while (!closed() && !game_over) {
        switch (kbhit()) {
            case GLFW_KEY_LEFT:
                if (!dir.x)
                    dir = {-1, 0};
                break;
            case GLFW_KEY_RIGHT:
                if (!dir.x)
                    dir = {1, 0};
                break;
            case GLFW_KEY_UP:
                if (!dir.y)
                    dir = {0, -1};
                break;
            case GLFW_KEY_DOWN:
                if (!dir.y)
                    dir = {0, 1};
                break;
        }
        if (frame++ % speed == 0) {
            cleardevice(COLOR::CYAN);
            auto next = s.next(dir);
            if (next.x == mouse.x && next.y == mouse.y) {
                s.body.push_front(mouse);
                mouse = s.mouse();
                if (++eaten % 5 == 0)
                    speed--;
            } else if (s.hit(next)) {
                game_over = true;
            } else {
                s.body.push_front(next);
                s.body.pop_back();
            }
            for (auto p : s.body)
                putpixel(p.x, p.y, COLOR::DARK_GRAY);
            putpixel(mouse.x, mouse.y, COLOR::BROWN);
        }
    }
    cout << "Score: " << eaten << '\n';
    closegraph();
}
