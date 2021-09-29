#include "AmbientLight.h"

AmbientLight::AmbientLight(const Color &color) : color(color) {}

void AmbientLight::apply(ShaderProgram &shaderProgram) {
    shaderProgram.set("ambient.color", color);
}
