#include "RelativeConstraint.h"

#include <utility>

RelativeConstraint::RelativeConstraint(ConstraintDirection direction, float percentage, std::string anchorId, bool relativePercentage) : Constraint(direction), percentage(percentage), anchorId(std::move(anchorId)), relativePercentage(relativePercentage) {}

ConstraintType RelativeConstraint::getType() {
    return RELATIVE;
}

float RelativeConstraint::getPercentage() const {
    return percentage;
}

void RelativeConstraint::setPercentage(float newPercentage) {
    percentage = newPercentage;
}

std::string RelativeConstraint::getAnchorId() {
    return anchorId;
}

void RelativeConstraint::apply(Vec2 &translation, Vec2 &scale, Vec2 *parentTranslation, Vec2 *parentScale) {
    Vec2 referenceScale(1.0f, 1.0f);

    if (parentScale != nullptr) {
        referenceScale = *parentScale;
    }

    if (anchorId != "parent") {
//        referenceScale = parent->findById(anchorId);
    }

    if (direction == HORIZONTAL) {
        if (relativePercentage) {
            scale.x = referenceScale.x * percentage;
        } else {
            scale.x = percentage;
        }
    }

    if (direction == VERTICAL) {
        if (relativePercentage) {
            scale.y = referenceScale.y * percentage;
        } else {
            scale.y = percentage;
        }
    }
}

void RelativeConstraint::apply(Vec2 &translation, Vec2 &scale, Vec2 &parentTranslation, Vec2 &parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    Vec2 referenceScale = parentScale;

    if (anchorId != "parent") {
//        referenceScale = parent->findById(anchorId);
    }

    if (direction == HORIZONTAL) {
        if (relativePercentage) {
            scale.x = referenceScale.x * percentage;
        } else {
            scale.x = percentage;
        }
    }

    if (direction == VERTICAL) {
        if (relativePercentage) {
            scale.y = referenceScale.y * percentage;
        } else {
            scale.y = percentage;
        }
    }
}
