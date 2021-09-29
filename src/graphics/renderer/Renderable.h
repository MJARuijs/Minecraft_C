#pragma once

#include "../shaders/ShaderProgram.h"

class Renderable {

public:
    virtual void render(ShaderProgram & shaderProgram) = 0;

};