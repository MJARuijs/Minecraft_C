#include "EntityRenderer.h"
#include "AnimatedEntity.h"
#include "StaticEntity.h"

EntityRenderer::EntityRenderer() : staticProgram("res/shaders/entities/entity.vert", "res/shaders/entities/entityForwardRendering.frag"), animatedProgram("res/shaders/entities/animatedEntity.vert", "res/shaders/entities/entityForwardRendering.frag") {}

void EntityRenderer::render(Camera &camera, AmbientLight &ambient, Sun &sun, const std::vector<Renderable *> &entities) {
    std::vector<Entity*> staticEntities;
    std::vector<Entity*> animatedEntities;

    for (auto & entity : entities) {
        Entity::Type type = reinterpret_cast<Entity*>(entity)->getType();
        if (type == Entity::ANIMATED) {
            animatedEntities.emplace_back(reinterpret_cast<AnimatedEntity*>(entity));
        } else {
            staticEntities.emplace_back(reinterpret_cast<StaticEntity*>(entity));
        }
    }

    render(staticProgram, camera, ambient, sun, staticEntities);
    render(animatedProgram, camera, ambient, sun, animatedEntities);
}

void EntityRenderer::render(ShaderProgram &program, Camera &camera, AmbientLight &ambient, Sun &sun, std::vector<Entity *> &entities) {
    program.start();

    program.set("projection", camera.projectionMatrix);
    program.set("view", camera.viewMatrix());
    program.set("cameraPosition", camera.getPosition());

    ambient.apply(program);
    sun.apply(program);

    for (auto & entity : entities) {
        if (entity->getType() == Entity::ANIMATED) {
            reinterpret_cast<AnimatedEntity*>(entity)->render(program);
        } else {
            entity->render(program);
        }
    }

    ShaderProgram::stop();
}
