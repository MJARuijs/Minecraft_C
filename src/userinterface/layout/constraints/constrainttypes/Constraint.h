#pragma once

#include <vector>
#include "../ConstraintDirection.h"
#include "ConstraintType.h"
#include "../../../../math/vectors/Vec2.h"

class Constraint {

protected:
    ConstraintDirection direction;

public:
    explicit Constraint(ConstraintDirection direction);

    ConstraintDirection getDirection();

    virtual void apply(Vec2 & translation, Vec2 & scale, Vec2 * parentTranslation, Vec2 * parentScale) = 0;
    virtual void apply(Vec2 & translation, Vec2 & scale, Vec2 & parentTranslation, Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings) = 0;
    virtual ConstraintType getType() = 0;

};