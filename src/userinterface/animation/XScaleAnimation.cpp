#include "XScaleAnimation.h"

XScaleAnimation::XScaleAnimation(float duration, Item * item, float toScale, std::function<void()> onFinish) : Animation(std::move(onFinish)), duration(duration), toScale(toScale), speed(0.0f), item(item) {}

bool XScaleAnimation::apply(float deltaTime) {

    if (!started) {
        started = true;
        speed = (toScale - item->getScale().x) / duration;
    }

    float increase = deltaTime * speed;

    if (std::abs(item->getScale().x - toScale) <= std::abs(increase)) {
        item->setScale(Vec2(toScale, item->getScale().y));
        return true;
    } else {
        item->addToScale(Vec2(increase, 0.0f));
    }

    return false;
}


