#include "Button.h"
#include "../UniversalParameters.h"
#include "TextBox.h"
#include "../layout/constraints/constrainttypes/RelativeConstraint.h"
#include "../layout/constraints/constrainttypes/CenterConstraint.h"

#include <utility>

Button::Button(const std::string &id, const ConstraintSet &constraints, Background *background,
               std::function<void()> onClick)
        : Item(id, constraints, background), onClick(std::move(onClick)), isHovered(false), isClicked(false) {}

bool Button::update(Mouse &mouse, float aspectRatio, float deltaTime) {
    if (Item::update(mouse, aspectRatio, deltaTime)) {
        return true;
    }

    bool isNowHovered = checkHovered(mouse, aspectRatio);

    if (!isHovered && isNowHovered) {
        std::vector<Animation *> animations;
        for (auto &hoverEffect : hoverEffects) {
            std::vector<Animation *> hoverAnimations = hoverEffect->applyOn(this);
            for (auto *hoverAnimation : hoverAnimations) {
                animations.emplace_back(hoverAnimation);
            }
        }
        addAnimations(animations);
    }

    if (isHovered && !isNowHovered) {
        std::vector<Animation *> animations;
        for (auto &hoverEffect : hoverEffects) {
            std::vector<Animation *> hoverAnimations = hoverEffect->removeFrom(this);
            for (auto *hoverAnimation : hoverAnimations) {
                animations.emplace_back(hoverAnimation);
            }
        }
        addAnimations(animations);
    }

    isHovered = isNowHovered;

    if (isHovered && mouse.isButtonPressed(GLFW_MOUSE_BUTTON_1)) {
        onClick();
        std::vector<Animation *> animations;
        for (auto &hoverEffect : clickEffects) {
            std::vector<Animation *> hoverAnimations = hoverEffect->applyOn(this);
            for (auto *hoverAnimation : hoverAnimations) {
                animations.emplace_back(hoverAnimation);
            }
        }
        addAnimations(animations);
        isClicked = true;
    }

    if (isClicked && mouse.isButtonReleased(GLFW_MOUSE_BUTTON_1)) {
        std::vector<Animation *> animations;
        for (auto &clickEffect : clickEffects) {
            std::vector<Animation *> clickAnimations = clickEffect->removeFrom(this);
            for (auto *clickAnimation : clickAnimations) {
                animations.emplace_back(clickAnimation);
            }
        }

        addAnimations(animations);
        isClicked = false;
    }
    if (isHovered || isClicked) {
        return true;
    }
    return false;
}

bool Button::checkHovered(Mouse &mouse, float aspectRatio) {
    return isMouseOnButton(mouse, aspectRatio);
}

bool Button::isMouseOnButton(Mouse &mouse, float aspectRatio) {
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

Button &Button::addHoverEffects(const std::vector<Effect *> &effects) {
    for (auto *effect : effects) {
        hoverEffects.emplace_back(effect);
    }
    return *this;
}

Button &Button::addClickEffects(const std::vector<Effect *> &effects) {
    for (auto *effect : effects) {
        clickEffects.emplace_back(effect);
    }
    return *this;
}

Button &Button::setOnClick(std::function<void()> newOnClick) {
    this->onClick = std::move(newOnClick);
    return *this;
}

Button &Button::setText(const std::string &text, Background *textBackground, const Color &color, const Color &outlineColor, Font * font) {
    add(new TextBox(getId() + "_text", ConstraintSet(
            new CenterConstraint(HORIZONTAL),
            new CenterConstraint(VERTICAL),
            new RelativeConstraint(HORIZONTAL, 1.0f),
            new RelativeConstraint(VERTICAL, 1.0f)
    ), text, 1.77f, 3.0f, textBackground, color, outlineColor, font));
    return *this;
}
