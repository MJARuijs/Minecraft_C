#include <stdexcept>
#include "../userinterface/UniversalParameters.h"

#include "Window.h"

Window::Window(const std::string& title, int width, int height) {
    this->width = width;
    this->height = height;
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    windowId = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (windowId == nullptr) {
        throw std::runtime_error("Failed to open GLFW windowId");
    }

    glfwMakeContextCurrent(windowId);
    glfwSwapInterval(1);

    fullScreen = false;
}

Window::~Window() {
    glfwDestroyWindow(windowId);
}

void Window::setBackgroundColor(float red, float green, float blue) {
    glClearColor(red, green, blue, 1.0f);
}

void Window::updateWindowSize() {
    int w;
    int h;

    glfwGetWindowSize(windowId, &w, &h);

    if (w != width || h != height) {
        width = w;
        height = h;

        UniversalParameters::aspectRatio = 1.0f;
        UniversalParameters::viewPortX = width;
        UniversalParameters::viewPortY = height;
//        callback->onSizeChanged(width, height);
    }
}

float Window::getAspectRatio() {
    updateWindowSize();
    return ((float)width / (float)height);
}

void Window::toggleFullScreen() {
    if (fullScreen) {
        glfwSetWindowMonitor(windowId, nullptr,
                             static_cast<int>(oldWindowPosition[0]),
                             static_cast<int>(oldWindowPosition[1]),
                             static_cast<int>(oldWindowSize[0]),
                             static_cast<int>(oldWindowSize[1]), 0);

        fullScreen = false;
    } else {
        int posX, posY;
        int sizeX, sizeY;
        glfwGetWindowPos(windowId, &posX, &posY);
        glfwGetWindowSize(windowId, &sizeX, &sizeY);
        oldWindowPosition[0] = (float) posX;
        oldWindowPosition[1] = (float) posY;

        oldWindowSize[0] = (float) sizeX;
        oldWindowSize[1] = (float) sizeY;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(windowId, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);

        fullScreen = true;
    }

}

void Window::resize(int width, int height) {
    glViewport(0, 0, width, height);
    UniversalParameters::viewPortX = width;
    UniversalParameters::viewPortY = height;
    UniversalParameters::aspectRatio = (float)width / (float)height;
}

bool Window::isClosed() {
    return static_cast<bool>(glfwWindowShouldClose(windowId));
}

void Window::show() {
    glfwFocusWindow(windowId);
    glfwShowWindow(windowId);
}

void Window::hide() {
    glfwHideWindow(windowId);
}

void Window::close() {
    glfwSetWindowShouldClose(windowId, true);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

void Window::synchronize() {
    glfwSwapBuffers(windowId);
}
