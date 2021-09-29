#include "Timer.h"

Timer::Timer() {
    double startTime = glfwGetTime();
    lastTime = startTime;
    currentTime = startTime;
}

void Timer::update() {
    lastTime = currentTime;
    currentTime = glfwGetTime();
}

float Timer::time() const {
    return (float)currentTime;
}

float Timer::delta() const {
    return float(currentTime - lastTime);
}