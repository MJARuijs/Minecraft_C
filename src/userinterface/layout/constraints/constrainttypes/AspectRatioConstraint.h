#pragma once

#include "Constraint.h"

class AspectRatioConstraint : public Constraint {

private:
    float aspectRatio;

public:
    AspectRatioConstraint(ConstraintDirection direction, float aspectRatio);

    void setAspectRatio(float newRatio);

    void apply(Vec2& translation, Vec2& scale, Vec2 * parentTranslation, Vec2 * parentScale) override;
    void apply(Vec2& translation, Vec2& scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) override;

    ConstraintType getType() override;
};