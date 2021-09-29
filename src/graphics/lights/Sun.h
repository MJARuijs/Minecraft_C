#pragma once

#include "../../math/Color.h"
#include "../shaders/ShaderProgram.h"

class Sun {

private:
    Color color;
    Vec3 direction;

public:
    Sun(const Color & color, const Vec3 & direction);

    void apply(ShaderProgram & shaderProgram);
};