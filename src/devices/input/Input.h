#pragma once

#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "Keyboard.h"

class Input {

public:
    Keyboard keyboard;
    Mouse mouse;

    Input();
    ~Input();

    void update(float centerX, float centerY);

    void onButtonPressed(int button, int action);
    void onCursorUpdate(double x, double y);
};

