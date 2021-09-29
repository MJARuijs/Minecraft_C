#pragma once

#include "../Animation.h"
#include "../../items/Item.h"

class Effect {

protected:
    float duration;

public:
    Effect();
    explicit Effect(float duration);

    virtual std::vector<Animation*> applyOn(Item * item) = 0;
    virtual std::vector<Animation*> removeFrom(Item * item) = 0;
};