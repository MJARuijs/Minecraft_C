#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include "../math/vectors/Vec2.h"

class Window {

private:
    GLFWwindow* windowId;
//    WindowSizeCallback* callback;
    int width;
    int height;
    bool fullScreen;
    Vec2 oldWindowPosition;
    Vec2 oldWindowSize;

public:
    Window(const std::string &title, int width, int height);
    ~Window();

    static void setBackgroundColor(float red, float green, float blue);
    bool isClosed();

    void synchronize();

    int getWidth() const;
    int getHeight() const;

    void updateWindowSize();
    float getAspectRatio();

    void toggleFullScreen();
    static void resize(int width, int height);
    void show();
    void hide();
    void close();
};
