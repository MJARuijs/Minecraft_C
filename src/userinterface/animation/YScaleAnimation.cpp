#include "YScaleAnimation.h"

YScaleAnimation::YScaleAnimation(float duration, Item * item, float toScale, std::function<void()> onFinish) : Animation(std::move(onFinish)), duration(duration), toScale(toScale), speed(0.0f), item(item) {}

bool YScaleAnimation::apply(float deltaTime) {

    if (!started) {
        started = true;
        speed = (toScale - item->getScale().y) / duration;
    }

    float increase = deltaTime * speed;

    if (std::abs(item->getScale().y - toScale) <= std::abs(increase)) {
        item->setScale(Vec2(item->getScale().x, toScale));
        return true;
    } else {
        item->addToScale(Vec2(0.0f, increase));
    }

    return false;
}


