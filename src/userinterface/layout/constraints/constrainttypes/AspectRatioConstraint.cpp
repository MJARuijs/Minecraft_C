#include "AspectRatioConstraint.h"

AspectRatioConstraint::AspectRatioConstraint(ConstraintDirection direction, float aspectRatio) : Constraint(direction), aspectRatio(aspectRatio) {}

void AspectRatioConstraint::setAspectRatio(float newRatio) {
    aspectRatio = newRatio;
}

void AspectRatioConstraint::apply(Vec2 &translation, Vec2 &scale, Vec2 *parentTranslation, Vec2 *parentScale) {
    if (direction == VERTICAL) {
        scale.y = scale.x * aspectRatio;
    }
    if (direction == HORIZONTAL) {
        scale.x = scale.y * aspectRatio;
    }
}

void AspectRatioConstraint::apply(Vec2 &translation, Vec2 &scale, Vec2 &parentTranslation, Vec2 &parentScale,const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> &siblings) {
    if (direction == VERTICAL) {
        scale.y = scale.x * aspectRatio;
    }
    if (direction == HORIZONTAL) {
        scale.x = scale.y * aspectRatio;
    }
}

ConstraintType AspectRatioConstraint::getType() {
    return ASPECT_RATIO;
}
