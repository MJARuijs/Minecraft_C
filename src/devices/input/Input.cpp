#include "Input.h"

Input::Input() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Keyboard::key_callback);
    glfwSetMouseButtonCallback(window, Mouse::button_callback);
    glfwSetCursorPosCallback(window, Mouse::cursor_callback);
}

Input::~Input() {
    GLFWwindow* window = glfwGetCurrentContext();
    glfwSetWindowUserPointer(window, nullptr);
    glfwSetKeyCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
}

void Input::update(float centerX, float centerY) {
    mouse.update(centerX, centerY);
    keyboard.update();
}

void Input::onButtonPressed(int button, int action) {
    mouse.onButtonPressed(button, action);
}

void Input::onCursorUpdate(double x, double y) {
    mouse.onCursorUpdate(x, y);
}
