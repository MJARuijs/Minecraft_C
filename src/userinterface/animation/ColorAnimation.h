#pragma once

#include "Animation.h"
#include "../items/Item.h"
#include "animationtypes/ColorAnimationType.h"
#include "../items/backgrounds/ColorType.h"

class ColorAnimation : public Animation {

private:
    float duration;
    Item * item;
    Color * otherColor;
    bool ignoreAlpha;

    float rSpeed;
    float gSpeed;
    float bSpeed;
    float aSpeed;

    ColorAnimationType animationType;
    ColorType colorType;
    Color startColor;
    Color goalColor;

public:
    ColorAnimation(float duration, Item * item, Color * otherColor, ColorAnimationType animationType, ColorType colorType, bool ignoreAlpha = true, std::function<void()> onFinish = [](){});

    bool apply(float deltaTime) override;

    Color increaseValues(Color currentColor, float deltaTime);
};