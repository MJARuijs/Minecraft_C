#include "Mouse.h"
#include "Input.h"

Mouse::Mouse(): cursorPosition(1.0f, 1.0f) {}

void Mouse::capture() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    captured = true;
}

void Mouse::release() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    captured = false;
}

void Mouse::toggle() {
    if (captured) {
        release();
    } else {
        capture();
    }
}

void Mouse::update(float& centerX, float& centerY) {
    GLFWwindow* window = glfwGetCurrentContext();
    buttonsPressed.clear();
    buttonsReleased.clear();

    delta.x = 0.0f;
    delta.y = 0.0f;

    if (captured) {
        cursorPosition.x = centerX;
        cursorPosition.y = centerY;
        glfwSetCursorPos(window, centerX, centerY);
    }
}

void Mouse::onButtonPressed(int button, int action) {
    switch (action) {
        case GLFW_PRESS:
            buttonsPressed.insert(button);
            buttonsDown.insert(button);
            break;
        case GLFW_RELEASE:
            buttonsReleased.insert(button);
            buttonsDown.erase(button);
            break;
    }
}

void Mouse::onCursorUpdate(double x, double y) {
    delta.x = (float)x - cursorPosition.x;
    delta.y = (float)y - cursorPosition.y;

    cursorPosition.x = ((float)x);
    cursorPosition.y = ((float)y);
}

bool Mouse::isButtonPressed(int buttonId) const {
    return buttonsPressed.count(buttonId) != 0;
}

bool Mouse::isButtonDown(int buttonId) const {
    return buttonsDown.count(buttonId) != 0;
}

bool Mouse::isButtonReleased(int buttonId) const {
    return buttonsReleased.count(buttonId) != 0;
}

void Mouse::button_callback(GLFWwindow* window, int button, int action, int mods) {
    void* data = glfwGetWindowUserPointer(window);
    auto * input = static_cast<Input*>(data);
    input->onButtonPressed(button, action);
}

void Mouse::cursor_callback(GLFWwindow* window, double x, double y) {
    void* data = glfwGetWindowUserPointer(window);
    auto * input = static_cast<Input*>(data);
    input->onCursorUpdate(x, y);
}
