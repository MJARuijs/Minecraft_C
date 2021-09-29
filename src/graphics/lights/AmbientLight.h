#pragma once

#include "../../math/Color.h"
#include "../shaders/ShaderProgram.h"

class AmbientLight {

private:
    Color color;

public:
    explicit AmbientLight(const Color & color);

    void apply(ShaderProgram & shaderProgram);
};