#include "Devices.h"

Devices::Devices() : window("OpenGl C++", 1280, 720) {
    Window::resize(1280, 720);
    Window::setBackgroundColor(0.25f, 0.25f, 0.25f);
}

Keyboard& Devices::keyboard() {
    return input.keyboard;
}

Mouse& Devices::mouse() {
    return input.mouse;
}

void Devices::update() {
    window.synchronize();
    timer.update();
    input.update((float)window.getWidth() / 2.0f, (float)window.getHeight() / 2.0f);
}

void Devices::showWindow() {
    window.show();
}
