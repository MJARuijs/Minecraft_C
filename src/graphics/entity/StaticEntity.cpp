#include "StaticEntity.h"

StaticEntity::StaticEntity(StaticModel *model, Mat4 transformation) : Entity(STATIC, model, std::move(transformation)) {}

StaticEntity::StaticEntity(StaticModel *model) : Entity(STATIC, model) {}

void StaticEntity::render(ShaderProgram &shaderProgram) {
    Entity::render(shaderProgram);
}
