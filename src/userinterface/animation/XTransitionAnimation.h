#pragma once

#include "Animation.h"
#include "../items/Item.h"

class XTransitionAnimation : public Animation {

private:
    float speed;
    float finalPoint;
    float translation;
    TransitionType type;
    Item * item;
    float duration;

public:
    XTransitionAnimation(float duration, Item* item, float translation, TransitionType type, std::function<void()> onFinish = [](){});

    bool apply(float deltaTime) override;

};