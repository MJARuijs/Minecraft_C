#pragma once

#include "mesh/Mesh.h"
#include "../material/Material.h"
#include "../shaders/ShaderProgram.h"

class Shape {

private:
    Mesh mesh;
    Material material;

public:
    Shape(const Mesh & mesh, Material  material);

    void render(ShaderProgram & shaderProgram);
};