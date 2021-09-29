#include <iostream>
#include <utility>
#include "PixelConstraint.h"
#include "../../../UniversalParameters.h"

PixelConstraint::PixelConstraint(ConstraintDirection direction, float offset, std::string anchorId) : Constraint(direction), offset(offset), anchorId(std::move(anchorId)) {}

std::string PixelConstraint::getAnchorId() {
    return anchorId;
}

float PixelConstraint::getOffset() const {
    return offset;
}

void PixelConstraint::setOffset(float newOffset) {
    offset = newOffset;
}

ConstraintType PixelConstraint::getType() {
    return PIXEL;
}

void PixelConstraint::apply(Vec2 & translation, Vec2 & scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    Vec2 referenceTranslation = parentTranslation;
    Vec2 referenceScale = parentScale;

    if (anchorId != "parent") {
        for (auto & sibling : siblings) {
            if (sibling.first == anchorId) {
                referenceTranslation = sibling.second.first;
                referenceScale = sibling.second.second;
            }
        }
    }

    if (direction == HORIZONTAL || direction == VERTICAL) {
        std::cout << "Invalid direction given for PixelConstraint!" << std::endl;
    }

    if (direction == TO_TOP) {
        float referenceTop = referenceTranslation.y + referenceScale.y;
        calculateTranslation(translation, referenceTop, scale, referenceScale, 1, true);
    }
    if (direction == TO_BOTTOM) {
        float referenceBottom = referenceTranslation.y - referenceScale.y;
        calculateTranslation(translation, referenceBottom, scale, referenceScale, 1, false);
    }
    if (direction == TO_LEFT) {
        float referenceLeft = referenceTranslation.x - referenceScale.x;
        calculateTranslation(translation, referenceLeft, scale, referenceScale, 0, false);
    }
    if (direction == TO_RIGHT) {
        float referenceRight = referenceTranslation.x + referenceScale.x;
        calculateTranslation(translation, referenceRight, scale, referenceScale, 0, true);
    }
}

void PixelConstraint::apply(Vec2 &translation, Vec2 &scale, Vec2 * parentTranslation, Vec2 * parentScale) {
    Vec2 referenceTranslation;
    Vec2 referenceScale(UniversalParameters::aspectRatio, 1.0f);

    if (parentTranslation != nullptr && parentScale != nullptr) {
        referenceTranslation = *parentTranslation;
        referenceScale = *parentScale;
    }

    if (anchorId != "parent") {
//        Item sibling = parent->findById(anchorId);
//        referenceTranslation = sibling.getGoalDimensions().first;
//        referenceScale = sibling.getGoalDimensions().second;
    }

    if (direction == HORIZONTAL || direction == VERTICAL) {
        std::cout << "Invalid direction given for PixelConstraint!" << std::endl;
    }

    if (direction == TO_TOP) {
        float referenceTop = referenceTranslation.y + referenceScale.y;
        calculateTranslation(translation, referenceTop, scale, referenceScale, 1, true);
    }
    if (direction == TO_BOTTOM) {
        float referenceBottom = referenceTranslation.y - referenceScale.y;
        calculateTranslation(translation, referenceBottom, scale, referenceScale, 1, false);
    }
    if (direction == TO_LEFT) {
        float referenceLeft = referenceTranslation.x - referenceScale.x;
        calculateTranslation(translation, referenceLeft, scale, referenceScale, 0, false);
    }
    if (direction == TO_RIGHT) {
        float referenceRight = referenceTranslation.x + referenceScale.x;
        calculateTranslation(translation, referenceRight, scale, referenceScale, 0, true);
    }
}

void PixelConstraint::calculateTranslation(Vec2 & translation, float reference, Vec2 &scale, Vec2 &referenceScale, int index, bool signFlipped) {
    float sign = signFlipped ? -1 : 1;

    if (anchorId == "parent") {
        translation[index] = reference + scale[index] * sign;
        translation[index] += offset * referenceScale[index] * 2.0f * sign;
    } else {
        translation[index] = reference - scale[index] * sign;
        translation[index] -= offset * referenceScale[index] * 2.0f * sign;
    }
}
