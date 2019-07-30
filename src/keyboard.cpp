#include "lfbg/graphics.h"

namespace lfbg {

// external objects

extern GLFWwindow* __window_handle__;
extern window_helper __window__helper_obj__;

// defined objects

bool __keyboard_is_pressed__[GLFW_KEY_LAST + 1];
bool __keyboard_is_up__[GLFW_KEY_LAST + 1];
bool __keyboard_is_down__[GLFW_KEY_LAST + 1];
int __kbhit__ = 0;

auto __default_keyboard_callback__ = [](int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(__window_handle__, GLFW_TRUE);
    if (action == GLFW_PRESS) {
        __keyboard_is_pressed__[key] = true;
        __keyboard_is_down__[key] = true;
    } else if (action == GLFW_RELEASE) {
        __keyboard_is_pressed__[key] = false;
        __keyboard_is_up__[key] = true;
        __kbhit__ = key;
    }
};

// functions

void kbreset(){
    for (size_t i = 0; i < GLFW_KEY_LAST + 1; i++)
        __keyboard_is_down__[i] = __keyboard_is_up__[i] = false;
}

void set_default_keyboard_callback() {
    __window__helper_obj__.keyboard_callback = __default_keyboard_callback__;
}

void set_keyboard_callback(std::function<void(int, int, int, int)> callback) {
    __window__helper_obj__.keyboard_callback = callback;
}

int kbhit() {
    bitblt();
    auto lastkey = __kbhit__;
    __kbhit__ = 0;
    return lastkey;
}

bool is_key_pressed(int key) { return __keyboard_is_pressed__[key]; }

bool is_key_down(int key) { return __keyboard_is_down__[key]; }

bool is_key_up(int key) { return __keyboard_is_up__[key]; }

} // namespace lfbg