#include "ConstraintSet.h"

#include <algorithm>
#include <iostream>
#include "constrainttypes/RelativeConstraint.h"
#include "constrainttypes/PixelConstraint.h"
#include "constrainttypes/AspectRatioConstraint.h"

ConstraintSet::ConstraintSet(std::vector<Constraint*> & constraints) : scale(1.0f, 1.0f) {
    for (auto & constraint : constraints) {
        this->constraints.emplace_back(constraint);
    }
}

ConstraintSet::ConstraintSet(Constraint * one, Constraint * two, Constraint * three, Constraint * four) : scale(1.0f, 1.0f) {
    constraints.emplace_back(one);
    constraints.emplace_back(two);
    constraints.emplace_back(three);
    constraints.emplace_back(four);
}

void ConstraintSet::operator+=(Constraint *constraint) {
    constraints.emplace_back(constraint);
}

Vec2 ConstraintSet::getTranslation() const {
    return Vec2(translation.x, translation.y);
}

Vec2 ConstraintSet::getScale() const {
    return Vec2(scale.x, scale.y);
}

void ConstraintSet::translate(const Vec2 & translationAddition) {
    this->translation.x += translationAddition.x;
    this->translation.y += translationAddition.y;
}

void ConstraintSet::place(const Vec2 &placement) {
    this->translation.x = placement.x;
    this->translation.y = placement.y;
}

void ConstraintSet::setScale(const Vec2 & newScale) {
    this->scale.x = newScale.x;
    this->scale.y = newScale.y;
}

void ConstraintSet::addToScale(const Vec2 &scaleAddition) {
    this->scale.x += scaleAddition.x;
    this->scale.y += scaleAddition.y;
}

std::vector<std::string> ConstraintSet::determineRequiredIds() {
    requiredIds.clear();

    for (auto & constraint : constraints) {
        if (constraint->getType() == RELATIVE) {
            std::string anchorId = dynamic_cast<RelativeConstraint*>(constraint)->getAnchorId();
            if (anchorId != "parent") {
                if (std::none_of(requiredIds.begin(), requiredIds.end(), [&](std::string & requiredId) {
                    if (requiredId == anchorId) {
                        return true;
                    }
                    return false;
                })) {
                    requiredIds.emplace_back(anchorId);
                }
            }
        } else if (constraint->getType() == PIXEL) {
            std::string anchorId = dynamic_cast<PixelConstraint*>(constraint)->getAnchorId();
            if (anchorId != "parent") {
                if (std::none_of(requiredIds.begin(), requiredIds.end(), [&](std::string & requiredId) {
                    if (requiredId == anchorId) {
                        return true;
                    }
                    return false;
                })) {
                    requiredIds.emplace_back(anchorId);
                }
            }
        }
    }

    return requiredIds;
}

void ConstraintSet::updateConstraint(const ConstraintType &type, const  ConstraintDirection &direction, float newValue) {
    for (auto & constraint : constraints) {
        if (constraint->getDirection() == direction) {
            if (type == PIXEL) {
                dynamic_cast<PixelConstraint*>(constraint)->setOffset(newValue);
            } else if (type == RELATIVE) {
                dynamic_cast<RelativeConstraint*>(constraint)->setPercentage(newValue);
            } else if (type == ASPECT_RATIO) {
                dynamic_cast<AspectRatioConstraint*>(constraint)->setAspectRatio(newValue);
            }
        }
    }
}

void ConstraintSet::apply() {
    sort();

    for (const auto & constraint : constraints) {
        constraint->apply(translation, scale, nullptr, nullptr);
    }
}

void ConstraintSet::apply(Vec2 parentTranslation, Vec2 parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    sort();

    for (const auto & constraint : constraints) {
        constraint->apply(translation, scale, parentTranslation, parentScale, siblings);
    }
}

std::pair<Vec2, Vec2> ConstraintSet::computeResult(Vec2 parentTranslation, Vec2 parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) {
    sort();

    Vec2 resultTranslation;
    Vec2 resultScale;

    for (auto & constraint : constraints) {
        constraint->apply(resultTranslation, resultScale, parentTranslation, parentScale, siblings);
    }

    return std::pair<Vec2, Vec2>(resultTranslation, resultScale);
}

void ConstraintSet::sort() {
    std::vector<Constraint*> unsortedConstraints;
    std::vector<bool> indicesUsed(constraints.size());

    for (int i = 0; i < constraints.size(); i++) {
        unsortedConstraints.emplace_back(constraints[i]);
        indicesUsed[i] = false;
    }

    constraints.clear();

    for (auto & constraint : unsortedConstraints) {
        if (constraint->getType() != PIXEL) {
            constraints.emplace_back(constraint);
        }
    }

    for (auto & constraint : unsortedConstraints) {
        if (constraint->getType() == PIXEL) {
            constraints.emplace_back(constraint);
        }
    }
}
