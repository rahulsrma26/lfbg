#include "lfbg/graphics.h"

namespace lfbg {

// external objects

extern GLFWwindow* __window_handle__;
extern int __screen_width__, __screen_height__;
extern window_helper __window__helper_obj__;

// defined objects

double __cursor_x__, __cursor_y__;
int __cursor_offset_x__ = 0, __cursor_offset_y__ = 0;
int __cursor_scale_x__ = 0, __cursor_scale_y__ = 0;
int __mouse_is_pressed__;
int __mouse_is_up__;
int __mouse_is_down__;

std::function<void(double, double)> __cursor_pos_callback__;
auto __default_cursor_pos_callback__ = [](double, double) {};

auto __cursor_pos_compute_callback__ = [](double xpos, double ypos) {
    __cursor_x__ = (xpos - __cursor_offset_x__) * __screen_width__ / __cursor_scale_x__;
    __cursor_x__ = std::clamp(__cursor_x__, 0.0, __screen_width__ - 1e-6);
    __cursor_y__ = (ypos - __cursor_offset_y__) * __screen_height__ / __cursor_scale_y__;
    __cursor_y__ = std::clamp(__cursor_y__, 0.0, __screen_height__ - 1e-6);
    __cursor_pos_callback__(__cursor_x__, __cursor_y__);
};

auto __default_mouse_button_callback__ = [](int button, int action, int) {
    if (action == GLFW_PRESS) {
        __mouse_is_pressed__ |= (1 << button);
        __mouse_is_down__ |= (1 << button);
    } else if (action == GLFW_RELEASE) {
        __mouse_is_pressed__ &= ~(1 << button);
        __mouse_is_up__ &= ~(1 << button);
    }
};

// functions

void mbreset() { __mouse_is_up__ = __mouse_is_down__ = 0; }

void set_default_cursor_pos_callback() {
    __cursor_pos_callback__ = __default_cursor_pos_callback__;
    __window__helper_obj__.cursor_pos_callback = __cursor_pos_compute_callback__;
}

void set_cursor_pos_callback(std::function<void(double, double)> callback) {
    __cursor_pos_callback__ = callback;
}

void set_default_mouse_button_callback() {
    __window__helper_obj__.mouse_button_callback = __default_mouse_button_callback__;
}

void set_mouse_button_callback(std::function<void(int, int, int)> callback) {
    __window__helper_obj__.mouse_button_callback = callback;
}

std::pair<double, double> get_cursor_pos() { return {__cursor_x__, __cursor_y__}; }

bool is_button_pressed(int button) { return __mouse_is_pressed__ & (1 << button); }

bool is_button_down(int button) { return __mouse_is_down__ & (1 << button); }

bool is_button_up(int button) { return __mouse_is_up__ & (1 << button); }

int get_button_status() { return __mouse_is_pressed__; }

} // namespace lfbg