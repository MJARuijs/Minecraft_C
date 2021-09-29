#include "Movable.h"

Movable::Movable(bool moveXAxis, bool moveYAxis) : moveXAxis(moveXAxis), moveYAxis(moveYAxis) {}

void Movable::update(Mouse &mouse) {
    if (mouse.isButtonReleased(GLFW_MOUSE_BUTTON_1)) {

    }
}
