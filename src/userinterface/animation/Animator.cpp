#include "Animator.h"
#include "XTransitionAnimation.h"
#include "YTransitionAnimation.h"
#include "XScaleAnimation.h"
#include "YScaleAnimation.h"

void Animator::operator+=(const std::vector<Animation *> & newAnimations) {
    animationQueue.emplace_back(newAnimations);
}

void Animator::update(float deltaTime) {

    if (animations.empty() && !animationQueue.empty()) {
        for (auto * animation : animationQueue.front()) {
            animations.emplace_back(animation);
        }
        animationQueue.pop_front();
    }
    for (auto * animation : animations) {
        if (animation->apply(deltaTime)) {
            for (int i = 0; i < animations.size(); i++) {
                if (animations[i] == animation) {
                    animations.erase(animations.begin() + i);
                }
            }
        }
    }

}

void Animator::apply(ConstraintSet &constraints, Item *item, float duration, const Vec2 &parentTranslation,
                     const Vec2 &parentScale, const std::vector<Animation *> &extraAnimations) {
    std::pair<Vec2, Vec2> goalDimensions = constraints.computeResult(parentTranslation, parentScale);
    item->setGoalTranslation(&goalDimensions.first);
    item->setGoalScale(&goalDimensions.second);

    animateLayoutTransition(item, duration, goalDimensions, extraAnimations);
}

void Animator::apply(ConstraintSet & constraints, Item *item, float duration, const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    std::pair<Vec2, Vec2> goalDimensions = constraints.computeResult(parentTranslation, parentScale, siblings);
    item->setGoalTranslation(&goalDimensions.first);
    item->setGoalScale(&goalDimensions.second);
    animateLayoutTransition(item, duration, goalDimensions);
}

void Animator::animateLayoutTransition(Item *item, float duration, std::pair<Vec2, Vec2> goalDimensions, const std::vector<Animation*>& extraAnimations) {
    std::vector<Animation*> requiredAnimations;
    requiredAnimations.reserve(extraAnimations.size());

    for (auto & animation : extraAnimations) {
        requiredAnimations.emplace_back(animation);
    }

    if (goalDimensions.first.x != item->getTranslation().x) {
        requiredAnimations.emplace_back(new XTransitionAnimation(duration, item, goalDimensions.first.x, PLACEMENT));
    }

    if (goalDimensions.first.y != item->getTranslation().y) {
        requiredAnimations.emplace_back(new YTransitionAnimation(duration, item, goalDimensions.first.y, PLACEMENT));
    }

    if (goalDimensions.second.x != item->getScale().x) {
        requiredAnimations.emplace_back(new XScaleAnimation(duration, item, goalDimensions.second.x));
    }

    if (goalDimensions.second.y != item->getScale().y) {
        requiredAnimations.emplace_back(new YScaleAnimation(duration, item, goalDimensions.second.y));
    }

    animationQueue.emplace_back(requiredAnimations);
}
