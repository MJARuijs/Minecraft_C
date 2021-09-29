#include "XTransitionAnimation.h"

XTransitionAnimation::XTransitionAnimation(float duration, Item * item, float translation, TransitionType type, std::function<void()> onFinish) : Animation(std::move(onFinish)), duration(duration), item(item), translation(translation), type(type), speed(0.0f), finalPoint(0.0f) {}

bool XTransitionAnimation::apply(float deltaTime) {
    if (!started) {
        started = true;

        if (type == MOVEMENT) {
            speed = translation / duration;
            finalPoint = item->getTranslation().x + translation;
        } else if (type == PLACEMENT) {
            speed = (translation - item->getTranslation().x) / duration;
            finalPoint = translation;
        }
        item->setGoalTranslation(new Vec2(finalPoint, item->getGoalTranslation().y));
    }

    float increase = deltaTime * speed;
    if (std::abs(item->getTranslation().x - finalPoint) <= std::abs(increase)) {
        item->place(Vec2(finalPoint, item->getTranslation().y));
        onFinish();
        return true;
    } else {
        item->translate(Vec2(increase, 0.0f));
    }

    return false;
}


