#include "Material.h"

Material::Material(const Color &diffuse, const Color &specular, float shininess) : diffuse(diffuse), specular(specular), shininess(shininess) {}

void Material::setProperties(ShaderProgram &shaderProgram) {
    shaderProgram.set("material.diffuse", diffuse);
    shaderProgram.set("material.specular", specular);
    shaderProgram.set("material.shininess", shininess);
}

Material::Material() : diffuse(), specular(), shininess(0.0f) {}
