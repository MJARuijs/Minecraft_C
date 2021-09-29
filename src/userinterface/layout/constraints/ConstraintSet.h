#include <vector>
#include "../../../math/vectors/Vec2.h"
#include "constrainttypes/Constraint.h"

class ConstraintSet {

private:
    std::vector<Constraint*> constraints;

    Vec2 translation;
    Vec2 scale;

    std::vector<std::string> requiredIds;

public:
    ConstraintSet() = default;
    explicit ConstraintSet(std::vector<Constraint*> & constraints);
    ConstraintSet(Constraint * one, Constraint * two, Constraint * three, Constraint * four);
    ~ConstraintSet() = default;

    void operator+=(Constraint * constraint);

    [[nodiscard]] Vec2 getTranslation() const;
    [[nodiscard]] Vec2 getScale() const;

    void translate(const Vec2 & translationAddition);
    void place(const Vec2 & placement);

    void setScale(const Vec2 & newScale);
    void addToScale(const Vec2 & scaleAddition);

    std::vector<std::string> determineRequiredIds();

    void updateConstraint(const ConstraintType & type, const ConstraintDirection & direction, float newValue);

    void apply();
    void apply(Vec2 parentTranslation, Vec2 parentScale,  const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings);
    std::pair<Vec2, Vec2> computeResult(Vec2 parentTranslation, Vec2 parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblings = std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>>());

    void sort();
};
