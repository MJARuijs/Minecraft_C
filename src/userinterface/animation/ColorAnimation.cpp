#include "ColorAnimation.h"

#include <utility>

ColorAnimation::ColorAnimation(float duration, Item *item, Color * otherColor, ColorAnimationType animationType, ColorType colorType, bool ignoreAlpha,
                               std::function<void()> onFinish) : Animation(std::move(onFinish)), duration(duration),
                                                                 item(item), otherColor(otherColor), animationType(animationType), colorType(colorType),
                                                                 ignoreAlpha(ignoreAlpha), rSpeed(0.0f), gSpeed(0.0f), bSpeed(0.0f), aSpeed(0.0f) {}

bool ColorAnimation::apply(float deltaTime) {
    if (!started) {
        started = true;
        if (colorType == BACKGROUND_COLOR) {
            startColor = dynamic_cast<ColoredBackground*>(item->getBackground())->getColor();

        } else if (colorType == OUTLINE_COLOR) {
            startColor = item->getBackground()->getOutlineColor();
        }

        if (animationType == ADD_TO_COLOR) {
            goalColor = startColor + *otherColor;
        } else if (animationType == CHANGE_TO_COLOR) {
            goalColor = *otherColor;
        }

        for (int i = 0; i < 4; i++) {
            if (goalColor[i] < 0.0f) {
                goalColor[i] = 0.0f;
            }
            if (goalColor[i] > 1.0f) {
                goalColor[i] = 1.0f;
            }
        }

        if (ignoreAlpha) {
            goalColor.setA(1.0f);
        }

        if (animationType == ADD_TO_COLOR) {
            rSpeed = (otherColor->getR()) / duration;
            gSpeed = (otherColor->getG()) / duration;
            bSpeed = (otherColor->getB()) / duration;
            aSpeed = (otherColor->getA()) / duration;
        } else if (animationType == CHANGE_TO_COLOR) {
            rSpeed = (otherColor->getR() - startColor.getR()) / duration;
            gSpeed = (otherColor->getG() - startColor.getG()) / duration;
            bSpeed = (otherColor->getB() - startColor.getB()) / duration;
            aSpeed = (otherColor->getA() - startColor.getA()) / duration;
        }
    }

    if (colorType == BACKGROUND_COLOR) {
        Color currentColor = dynamic_cast<ColoredBackground*>(item->getBackground())->getColor();
        Color newColor = increaseValues(currentColor, deltaTime);
        dynamic_cast<ColoredBackground*>(item->getBackground())->setColor(newColor);
        if (newColor == goalColor) {
            onFinish();
            return true;
        }
    } else if (colorType == OUTLINE_COLOR) {
        Color currentColor = item->getBackground()->getOutlineColor();
        Color newColor = increaseValues(currentColor, deltaTime);
        item->getBackground()->setOutlineColor(newColor);
        if (newColor == goalColor) {
            onFinish();
            return true;
        }
    }

    return false;
}

Color ColorAnimation::increaseValues(Color currentColor, float deltaTime) {
    std::vector<float> increaseValues;
    increaseValues.emplace_back(deltaTime * rSpeed);
    increaseValues.emplace_back(deltaTime * gSpeed);
    increaseValues.emplace_back(deltaTime * bSpeed);
    increaseValues.emplace_back(deltaTime * aSpeed);

    for (int i = 0; i < 4; i++) {
        if (std::abs(currentColor[i] - goalColor[i]) <= std::abs(increaseValues[i])) {
            if (animationType == CHANGE_TO_COLOR) {
                currentColor[i] = otherColor->get(i);
            } else if (animationType == ADD_TO_COLOR) {
                currentColor[i] = startColor[i] + otherColor->get(i);
            }
        } else {
            currentColor[i] = currentColor[i] + increaseValues[i];
        }

        if (currentColor[i] < 0.0f) {
            currentColor[i] = 0.0f;
        }
        if (currentColor[i] > 1.0f) {
            currentColor[i] = 1.0f;
        }
    }

    return currentColor;
}
