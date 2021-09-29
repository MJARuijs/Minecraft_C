#pragma once

#include <stdexcept>
#include <GLFW/glfw3.h>

class GLFW {

public:
    GLFW() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    ~GLFW() {
        glfwTerminate();
    }

    void poll() {
        glfwPollEvents();
    }
};