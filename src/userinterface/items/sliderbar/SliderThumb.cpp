#include "SliderThumb.h"
#include "../../UniversalParameters.h"

#include <utility>

SliderThumb::SliderThumb(std::string id, const ConstraintSet &constraints, Background *background) : Item(std::move(id),
                                                                                                          constraints,
                                                                                                          background),
                                                                                                     moving(false),
                                                                                                     parentMaxX(0.0f),
                                                                                                     parentMinX(0.0f) {

}

bool SliderThumb::update(Mouse &mouse, float aspectRatio, float deltaTime) {

    if (mouse.isButtonDown(GLFW_MOUSE_BUTTON_1) && isMouseOnButton(mouse, aspectRatio)) {
        moving = true;
    }

    if (moving && mouse.isButtonDown(GLFW_MOUSE_BUTTON_1)) {
        if (mouse.delta.x != 0.0f || mouse.delta.y != 0.0f) {
            float mouseXPosition =
                    ((float) mouse.cursorPosition.x / (float) UniversalParameters::viewPortX) * 2.0f - 1.0f;

            if (mouseXPosition * aspectRatio >= parentMinX && mouseXPosition * aspectRatio <= parentMaxX) {
                place(Vec2(mouseXPosition * aspectRatio, getTranslation().y));
            }
        }
    }

    if (moving && !mouse.isButtonDown(GLFW_MOUSE_BUTTON_1)) {
        moving = false;
    }
    return true;
}

bool SliderThumb::isMouseOnButton(Mouse &mouse, float aspectRatio) {

    float minX = (getTranslation().x - getScale().x) / aspectRatio;
    float maxX = (getTranslation().x + getScale().x) / aspectRatio;
    float minY = getTranslation().y - getScale().y;
    float maxY = getTranslation().y + getScale().y;

    float scaledMouseX = ((float) mouse.cursorPosition.x / (float) UniversalParameters::viewPortX) * 2.0f - 1.0f;
    float scaledMouseY = -1 * (((float) mouse.cursorPosition.y / (float) UniversalParameters::viewPortY) * 2.0f - 1.0f);

    if (scaledMouseX < minX || scaledMouseX > maxX) {
        return false;
    }

    if (scaledMouseY < minY || scaledMouseY > maxY) {
        return false;
    }
    return true;
}

void SliderThumb::position(const Vec2 &parentTranslation, const Vec2 &parentScale,
                           const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> &siblingData) {

    Item::position(parentTranslation, parentScale, siblingData);
    parentMinX = parentTranslation.x - parentScale.x;
    parentMaxX = parentTranslation.x + parentScale.x;
}
