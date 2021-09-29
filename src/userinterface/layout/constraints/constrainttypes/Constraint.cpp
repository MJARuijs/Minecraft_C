#include "Constraint.h"

Constraint::Constraint(ConstraintDirection direction) : direction(direction) {}

ConstraintDirection Constraint::getDirection() {
    return direction;
}
