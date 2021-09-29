#pragma once

#include <GLFW/glfw3.h>

class Timer {

private:
    double lastTime;
    double currentTime;

public:

    Timer();
    ~Timer() = default;

    void update();
    float time() const;
    float delta() const;
};

