#pragma once

#include "Effect.h"
#include "../XTransitionAnimation.h"
#include "../YTransitionAnimation.h"
#include "../../UniversalParameters.h"

class TranslationEffect : public Effect {

private:
    float xTranslation;
    float yTranslation;

public:
    TranslationEffect(float xTranslation, float yTranslation, float duration = UniversalParameters::animationDuration);

    std::vector<Animation*> applyOn(Item * item) override;
    std::vector<Animation*> removeFrom(Item * item) override;

};