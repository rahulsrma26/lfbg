#include <stdlib.h>
#include <string>
#include <complex>
#include <vector>
#include "lfbg/graphics.h"

constexpr float G = 6.6740831e-11;
typedef std::complex<double> vector2f;
double speed = 1;

struct body {
    vector2f position;
    vector2f velocity;
    vector2f accelaration;
    double mass;

    void start() { accelaration = vector2f(0, 0); }
    void end() {
        velocity += accelaration * speed;
        position += velocity * speed;
    }
    void add_force(const body& o) {
        auto direction = o.position - position;
        double acc_mag = G * o.mass / (4 + std::norm(direction));
        accelaration += direction * acc_mag;
    }
};

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace lfbg;

    constexpr int width = 512, height = 512;
    if (argc > 1)
        speed = std::stod(argv[1]);
    int n_bodies = 1000;
    if (argc > 2)
        n_bodies = std::stoi(argv[2]);

    initgraph(width, height, 1, RenderType::Smooth, 1);
    vector<body> bodies(n_bodies);
    int limit = (width + height) / 8;
    for (auto& b : bodies) {
        b.mass = 100000 + rand() % 10000000;
        double angle = (rand() % 3141592) * 2e-6;
        double radius = rand() % limit;
        b.position = vector2f(width / 2 + radius * sin(angle), height / 2 + radius * cos(angle));
        b.velocity = vector2f(0, 0);
    }

    for (; cleardevice(COLOR::BLACK), !closed(); bitblt()) {
        vector2f avg_pos(0, 0);
        for (int i = 0; i < n_bodies; i++) {
            bodies[i].start();
            for (int j = 0; j < n_bodies; j++)
                if (i != j)
                    bodies[i].add_force(bodies[j]);
            bodies[i].end();
            avg_pos -= bodies[i].position;
        }
        avg_pos /= n_bodies;
        avg_pos += vector2f(width / 2, height / 2);
        for (auto& b : bodies) {
            b.position += avg_pos;
            int x = b.position.real(), y = b.position.imag();
            if (0 <= x && x < width && 0 <= y && y < height)
                putpixel(x, y, COLOR::WHITE);
        }
    }
    closegraph();
}
