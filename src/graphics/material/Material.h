#pragma once

#include "../../math/Color.h"
#include "../shaders/ShaderProgram.h"

class Material {

private:
    Color diffuse;
    Color specular;
    float shininess;

public:
    Material(const Color & diffuse, const Color & specular, float shininess);
    Material();

    void setProperties(ShaderProgram & shaderProgram);

};