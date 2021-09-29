#pragma once

#include "Animation.h"
#include "../items/Item.h"

class XScaleAnimation : public Animation {

private:
    float speed;
    float toScale;
    Item * item;
    float duration;

public:
    XScaleAnimation(float duration, Item * item, float toScale, std::function<void()> onFinish = [](){});

    bool apply(float deltaTime) override;
};
