#pragma once

#include "input/Input.h"
#include "Timer.h"

class Devices {

public:
    Devices();
    ~Devices() = default;

    Window window;
    Timer timer;
    Input input;

    Keyboard & keyboard();
    Mouse & mouse();

    void update();
    void showWindow();
};

