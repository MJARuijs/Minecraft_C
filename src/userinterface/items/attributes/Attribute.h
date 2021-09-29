#pragma once

#include "../../../devices/input/Mouse.h"

class Attribute {

public:
    virtual void update(Mouse & mouse) = 0;
};