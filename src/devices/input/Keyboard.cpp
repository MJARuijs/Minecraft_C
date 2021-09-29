#include "Keyboard.h"

Keyboard::Keyboard() = default;

bool Keyboard::keyPressed(int key) {
    return keysPressed.count(key) != 0;
}

bool Keyboard::keyHeld(int key) {
    return keysHeld.count(key) != 0;
}

bool Keyboard::keyReleased(int key) {
    return keysReleased.count(key) != 0;
}

bool Keyboard::keyDown(int key) {
    return keysDown.count(key) != 0;
}

void Keyboard::update() {
    keysPressed.clear();
    keysReleased.clear();
    keysHeld.clear();
}

void Keyboard::onKey(int key, int action) {
    switch (action) {
        case GLFW_PRESS:
            keysPressed.insert(key);
            keysDown.insert(key);
            break;
        case GLFW_REPEAT:
            keysHeld.insert(key);
            keysDown.insert(key);
            break;
        case GLFW_RELEASE:
            keysHeld.erase(key);
            keysDown.erase(key);
            keysReleased.insert(key);
            break;
    }
}

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    void* data = glfwGetWindowUserPointer(window);
    auto * input = static_cast<Keyboard*>(data);
    input->onKey(key, action);
}
