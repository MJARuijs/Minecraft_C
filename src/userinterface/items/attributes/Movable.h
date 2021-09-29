#pragma once

#include "Attribute.h"

class Movable : public Attribute {

private:
    bool moveXAxis;
    bool moveYAxis;

public:
    Movable(bool moveXAxis, bool moveYAxis);

    void update(Mouse & mouse) override;

};