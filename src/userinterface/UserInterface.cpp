#include "UserInterface.h"
#include "UniversalParameters.h"

UserInterface::UserInterface(float aspectRatio) : aspectRatio(aspectRatio), shaderProgram("res/shaders/ui.vert", "res/shaders/ui.frag"), textProgram("res/shaders/text.vert", "res/shaders/text.frag"), appliedLayout("default") {}

void UserInterface::showWindow(const std::string & name) {
    for (auto & window : windows) {
        if (window.getId() == name) {
            window.setShouldShow(true);
        } else {
            window.setShouldShow(false);
        }
    }
    showingId = name;
}

void UserInterface::hideWindows() {
    for (auto & window : windows) {
        window.setShouldShow(false);
    }
}

void UserInterface::operator+=(UIWindow & window) {
    windows.emplace_back(window);
}

void UserInterface::operator+=(UILayout & layout) {
    layouts.emplace_back(layout);
}

bool UserInterface::isShowing() {
    if (std::any_of(windows.begin(), windows.end(), [](UIWindow & w) {
        return w.shouldShow();
    })) {
        return true;
    }

    return false;
}

void UserInterface::applyLayout(const std::string & name, float duration) {
    for (auto & window : windows) {
        if (window.getId() == showingId) {
            for (auto & layout : layouts) {
                if (layout.getId() == name) {
                    window.applyLayout(layout, duration);
                    appliedLayout = layout.getId();
                }
            }
        }
    }
}

std::string UserInterface::getAppliedLayoutId() {
    return appliedLayout;
}

void UserInterface::update(Mouse &mouse, float deltaTime) {
    for (auto & window : windows) {
        if (window.shouldShow()) {
            window.update(mouse, aspectRatio, deltaTime);
        }
    }

    if (!showingId.empty()) {
        for (auto & window : windows) {
            if (window.getId() == showingId && !window.shouldShow()) {
                showingId = "";
                mouse.capture();
            }
        }
    }
}

void UserInterface::draw() {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    shaderProgram.start();
//    shaderProgram.set("aspectRatio", UniversalParameters::aspectRatio);
    shaderProgram.set("viewPort", Vec2((float)UniversalParameters::viewPortX, (float)UniversalParameters::viewPortY));

    for (auto & window : windows) {
        if (window.shouldShow()) {
            window.draw(shaderProgram, textProgram);
        }
    }

    ShaderProgram::stop();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
