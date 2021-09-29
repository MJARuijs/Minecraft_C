#pragma once

#include "../Item.h"

class SliderBar : public Item {

private:
    Item * thumb;

public:
    SliderBar(std::string id, const ConstraintSet & constraints, Background * background);

};