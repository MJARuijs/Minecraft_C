#include "TranslationEffect.h"

TranslationEffect::TranslationEffect(float xTranslation, float yTranslation, float duration) : Effect(duration), xTranslation(xTranslation), yTranslation(yTranslation) {}

std::vector<Animation *> TranslationEffect::applyOn(Item* item) {
    std::vector<Animation*> animations;

    if (xTranslation != 0.0f) {
        animations.emplace_back(new XTransitionAnimation(duration, item, item->getBasePosition().x + xTranslation, PLACEMENT));
    }
    if (yTranslation != 0.0f) {
        animations.emplace_back(new YTransitionAnimation(duration, item, item->getBasePosition().y + yTranslation, PLACEMENT));
    }
    return animations;
}

std::vector<Animation *> TranslationEffect::removeFrom(Item* item) {
    std::vector<Animation*> animations;

    if (xTranslation != 0.0) {
        animations.emplace_back(new XTransitionAnimation(duration, item, item->getBasePosition().x, PLACEMENT));
    }
    if (yTranslation != 0.0f) {
        animations.emplace_back(new YTransitionAnimation(duration, item, item->getBasePosition().y, PLACEMENT));
    }
    return animations;
}
