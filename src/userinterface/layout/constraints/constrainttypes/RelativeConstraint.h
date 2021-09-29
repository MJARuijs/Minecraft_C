#pragma once

#include "Constraint.h"

class RelativeConstraint : public Constraint {

private:
    float percentage;
    std::string anchorId;
    bool relativePercentage;

public:
    RelativeConstraint(ConstraintDirection direction, float percentage, std::string anchorId = "parent", bool relativePercentage = true);

    [[nodiscard]] float getPercentage() const;
    void setPercentage(float newPercentage);
    std::string getAnchorId();

    void apply(Vec2 & translation, Vec2 & scale, Vec2 * parentTranslation, Vec2 * parentScale) override;
    void apply(Vec2 & translation, Vec2 & scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) override;

    ConstraintType getType() override;
};