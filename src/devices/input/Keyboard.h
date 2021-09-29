#pragma once

#include <set>
#include "../Window.h"

class Keyboard {

public:
    Keyboard();
    ~Keyboard() = default;

    std::set<int> keysDown;
    std::set<int> keysPressed;
    std::set<int> keysHeld;
    std::set<int> keysReleased;

    bool keyDown(int key);
    bool keyPressed(int key);
    bool keyHeld(int key);
    bool keyReleased(int key);

    void update();
    void onKey(int key, int action);

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
