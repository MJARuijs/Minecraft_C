#include "CenterConstraint.h"

CenterConstraint::CenterConstraint(ConstraintDirection direction, float offset) : Constraint(direction), direction(direction), offset(offset) {}

void CenterConstraint::apply(Vec2 & translation, Vec2 & scale, Vec2 * parentTranslation, Vec2 * parentScale) {
    Vec2 referenceTranslation;
    Vec2 referenceScale;

    if (parentTranslation != nullptr) {
        referenceTranslation = *parentTranslation;
    }
    if (parentScale != nullptr) {
        referenceScale = *parentScale;
    }

    if (direction == HORIZONTAL) {
        if (offset == std::numeric_limits<float>::max()) {
            translation.x = referenceTranslation.x;
        } else {
            translation.x = referenceTranslation.x + (offset - 0.5f) * referenceScale.x;
        }
    } else if (direction == VERTICAL) {
        if (offset == std::numeric_limits<float>::max()) {
            translation.y = referenceTranslation.y;
        } else {
            translation.y = referenceTranslation.y + (offset - 0.5f) * referenceScale.y;
        }
    } else {
        std::cout << "Invalid direction given for CenterConstraint!" << std::endl;
    }
}

void CenterConstraint::apply(Vec2 & translation, Vec2 & scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    if (direction == HORIZONTAL) {
        if (offset == std::numeric_limits<float>::max()) {
            translation.x = parentTranslation.x;
        } else {
            translation.x = parentTranslation.x + (offset * 2.0f - 1.0f) * parentScale.x;
        }
    } else if (direction == VERTICAL) {
        if (offset == std::numeric_limits<float>::max()) {
            translation.y = parentTranslation.y;
        } else {
            translation.y = parentTranslation.y + (offset) * parentScale.y;
        }
    } else {
        std::cout << "Invalid direction given for CenterConstraint!" << std::endl;
    }
}

ConstraintType CenterConstraint::getType() {
    return CENTER;
}

