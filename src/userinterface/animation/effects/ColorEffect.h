#pragma once

#include "../../../math/Color.h"
#include "../../UniversalParameters.h"
#include "Effect.h"
#include "../ColorAnimation.h"

class ColorEffect : public Effect {

private:
    Color changeToColor;
    ColorType colorType;
    ColorAnimationType animationType;

public:
    ColorEffect(const Color & changeToColor, ColorType colorType, ColorAnimationType animationType, float duration = UniversalParameters::animationDuration);

    std::vector<Animation*> applyOn(Item * item) override;
    std::vector<Animation*> removeFrom(Item * item) override;

};