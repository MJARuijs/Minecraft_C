#pragma once

#include <algorithm>
#include "../graphics/shaders/ShaderProgram.h"
#include "containers/window/UIWindow.h"

class UserInterface {

private:
    float aspectRatio;
    ShaderProgram shaderProgram;
    ShaderProgram textProgram;

    std::vector<UIWindow> windows;
    std::vector<UILayout> layouts;

    std::string showingId;
    std::string appliedLayout;

public:
    explicit UserInterface(float aspectRatio);

    void operator+=(UIWindow & window);
    void operator+=(UILayout & layout);

    void showWindow(const std::string & name);
    void hideWindows();
    bool isShowing();

    void applyLayout(const std::string & name, float duration);
    std::string getAppliedLayoutId();

    void draw();
    void update(Mouse & mouse, float deltaTime);

};