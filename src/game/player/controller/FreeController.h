#pragma once

#include "../../Camera.h"
#include "../../../devices/input/Keyboard.h"
#include "../../../devices/input/Mouse.h"
#include "../../../util/Logger.h"

#define MOUSE_SPEED 0.005f
#define MOVE_SPEED 5.0f

class FreeController {

private:
    Vec3 position;
    Vec3 rotation;

public:
    FreeController(const Vec3 & position);

    void set();

    void update(Camera & camera, Mouse & mouse, Keyboard & keyboard, float delta);

};