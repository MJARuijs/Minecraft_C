#include "YTransitionAnimation.h"

YTransitionAnimation::YTransitionAnimation(float duration, Item * item, float translation, TransitionType type, std::function<void()> onFinish) : Animation(std::move(onFinish)), duration(duration), item(item), translation(translation), type(type), speed(0.0f), finalPoint(0.0f) {}

bool YTransitionAnimation::apply(float deltaTime) {
    if (!started) {
        started = true;

        if (type == MOVEMENT) {
            speed = translation / duration;
            finalPoint = item->getTranslation().y + translation;
        } else if (type == PLACEMENT) {
            speed = -(item->getTranslation().y - translation) / duration;
            finalPoint = translation;
        }
        item->setGoalTranslation(new Vec2(item->getGoalTranslation().x, finalPoint));
    }

    float increase = deltaTime * speed;
    if (std::abs(item->getTranslation().y - finalPoint) <= std::abs(increase)) {
        item->place(Vec2(item->getTranslation().x, finalPoint));
        onFinish();
        return true;
    } else {
        item->translate(Vec2(0.0f, increase));
    }

    return false;
}


