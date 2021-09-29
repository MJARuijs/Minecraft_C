#include "Entity.h"

#include <utility>

Entity::Entity(Type type, StaticModel * model, Mat4 transformation) : type(type), model(model), transformation(std::move(transformation)) {}

Entity::Entity(Type type, StaticModel * model) : type(type), model(model), transformation() {}

void Entity::render(ShaderProgram &shaderProgram) {
    shaderProgram.set("model", transformation);
    model->render(shaderProgram);
}

Entity::Type Entity::getType() const {
    return type;
}
