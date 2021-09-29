#include "ColorEffect.h"

ColorEffect::ColorEffect(const Color & changeToColor, ColorType colorType, ColorAnimationType animationType, float duration) : Effect(duration), changeToColor(changeToColor), colorType(colorType), animationType(animationType) {}

std::vector<Animation *> ColorEffect::applyOn(Item *item) {
    if (animationType == ADD_TO_COLOR) {
        if (colorType == BACKGROUND_COLOR) {
            for (int i = 0; i < 4; i++) {
                if (changeToColor[i] + dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i] > 1.0f) {
                    changeToColor[i] = 1.0f - dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i] > 1.0f;
                }
                if (changeToColor[i] + dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i] < 0.0f) {
                    changeToColor[i] = dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i];
                }
            }
        } else if (colorType == OUTLINE_COLOR) {
            for (int i = 0; i < 4; i++) {
                if (changeToColor[i] + item->getBackground()->getOutlineColor()[i] > 1.0f) {
                    changeToColor[i] = 1.0f - dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i] > 1.0f;
                }
                if (changeToColor[i] + item->getBackground()->getOutlineColor()[i] < 0.0f) {
                    changeToColor[i] = dynamic_cast<ColoredBackground*>(item->getBackground())->getColor()[i];
                }
            }
        }

    }
    std::vector<Animation*> animations;
    animations.emplace_back(new ColorAnimation(duration, item, new Color(changeToColor), animationType, colorType));
    return animations;
}

std::vector<Animation *> ColorEffect::removeFrom(Item *item) {
    std::vector<Animation*> animations;
    if (animationType == CHANGE_TO_COLOR) {
        animations.emplace_back(new ColorAnimation(duration, item, new Color(dynamic_cast<ColoredBackground*>(item->getBaseBackground())->getColor()), animationType, colorType));
    } else if (animationType == ADD_TO_COLOR) {
        animations.emplace_back(new ColorAnimation(duration, item, new Color(-changeToColor), animationType, colorType));
    }
    return animations;
}
