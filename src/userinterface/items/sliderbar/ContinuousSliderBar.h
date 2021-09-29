#pragma once

#include "../Item.h"
#include "SliderThumb.h"

class ContinuousSliderBar : public Item {

private:
    float min;
    float max;
    float position;
    SliderThumb * thumb;

public:
    ContinuousSliderBar(std::string id, const ConstraintSet & constraints, float min, float max, float position, Background * background, Background * thumbBackground);


};