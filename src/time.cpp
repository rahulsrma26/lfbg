#include "lfbg/graphics.h"

namespace lfbg {

// external objects

extern GLFWwindow* __window_handle__;
extern std::string __window_title__;

// defined objects

bool __show_fps__ = true;
double __last_time__, __last_fps__;
int __frames_till_last_fps__;

// functions

void delay(int miliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds)); }

void show_fps() { __show_fps__ = true; }

void hide_fps() {
    __show_fps__ = false;
    glfwSetWindowTitle(__window_handle__, __window_title__.c_str());
}

void init_fps(){
    __last_time__ = glfwGetTime();
    __last_fps__ = -1;
    __frames_till_last_fps__ = 0;
}

void update_fps(){
    if (__show_fps__) {
        __frames_till_last_fps__++;
        double curTime = glfwGetTime();
        double delta = curTime - __last_time__;
        if (delta >= 1.0) {
            double fps = __frames_till_last_fps__ / delta;
            // if (__last_fps__ > 0)
            //     fps = 0.3 * fps + 0.7 * __last_fps__;
            std::string title = __window_title__ + " fps: " + std::to_string(fps);
            glfwSetWindowTitle(__window_handle__, title.c_str());
            __frames_till_last_fps__ = 0;
            __last_time__ = curTime;
            __last_fps__ = fps;
        }
    }
}

} // namespace lfbg