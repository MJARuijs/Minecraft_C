#include "Sun.h"

Sun::Sun(const Color &color, const Vec3 &direction) : color(color), direction(direction) {}

void Sun::apply(ShaderProgram &shaderProgram) {
    shaderProgram.set("sun.color", color);
    shaderProgram.set("sun.direction", direction);
}
