#pragma once

#include <list>
#include "Animation.h"
#include "../items/Item.h"

class Animator {

private:
    std::vector<Animation*> animations;
    std::list<std::vector<Animation*>> animationQueue;

    std::map<std::string, Item*> postPonedChildren;

public:
    Animator() = default;

    void operator+=(const std::vector<Animation*> & newAnimations);

    void update(float deltaTime);

    void apply(ConstraintSet & constraints, Item *item, float duration, const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<Animation*>& extraAnimations = std::vector<Animation*>());
    void apply(ConstraintSet & constraints, Item *item, float duration, const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings);
    void animateLayoutTransition(Item * item, float duration, std::pair<Vec2, Vec2> goalDimensions, const std::vector<Animation*>& extraAnimations = std::vector<Animation*>());

};