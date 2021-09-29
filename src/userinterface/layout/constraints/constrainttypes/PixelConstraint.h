#pragma once

#include "Constraint.h"

class PixelConstraint : public Constraint {

private:
    float offset;
    std::string anchorId;

public:
    explicit PixelConstraint(ConstraintDirection direction, float offset = 0.0f, std::string anchorId = "parent");

    [[nodiscard]] float getOffset() const;
    void setOffset(float newOffset);
    std::string getAnchorId();

    void apply(Vec2 & translation, Vec2 & scale, Vec2 * parentTranslation, Vec2 * parentScale) override;
    void apply(Vec2 & translation, Vec2 & scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) override;
    ConstraintType getType() override;

    void calculateTranslation(Vec2 & translation, float reference, Vec2 & scale, Vec2 & referenceScale, int index, bool signFlipped);
};