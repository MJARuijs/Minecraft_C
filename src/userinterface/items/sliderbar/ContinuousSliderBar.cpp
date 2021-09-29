#include "ContinuousSliderBar.h"
#include "../../layout/constraints/constrainttypes/CenterConstraint.h"
#include "../../layout/constraints/constrainttypes/RelativeConstraint.h"
#include "../../layout/constraints/constrainttypes/AspectRatioConstraint.h"

#include <utility>

ContinuousSliderBar::ContinuousSliderBar(std::string id, const ConstraintSet &constraints, float min, float max,
                                         float position, Background *background, Background *thumbBackground)

        : Item(std::move(id), constraints, background), thumb(nullptr), min(min), max(max), position(position) {

    thumb = new SliderThumb(id + "_thumb", ConstraintSet(
        new CenterConstraint(VERTICAL),
        new CenterConstraint(HORIZONTAL, position),
        new RelativeConstraint(VERTICAL, 1.5f),
        new AspectRatioConstraint(HORIZONTAL, 1.0f)
    ), thumbBackground);

    add(thumb);
}
