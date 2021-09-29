#include "Shape.h"

#include <utility>

Shape::Shape(const Mesh &mesh, Material material) : mesh(mesh), material(std::move(material)) {}

void Shape::render(ShaderProgram &shaderProgram) {
    material.setProperties(shaderProgram);
    mesh.render();
}
