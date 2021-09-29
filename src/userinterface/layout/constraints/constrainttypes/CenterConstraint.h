#pragma once

#include "Constraint.h"
#include <iostream>

class CenterConstraint : public Constraint {

private:
    ConstraintDirection direction;
    float offset;

public:
    explicit CenterConstraint(ConstraintDirection direction, float offset = std::numeric_limits<float>::max());

    void apply(Vec2& translation, Vec2& scale, Vec2 * parentTranslation, Vec2 * parentScale) override;
    void apply(Vec2& translation, Vec2& scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) override;

    ConstraintType getType() override;
};