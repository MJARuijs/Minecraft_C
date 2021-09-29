#pragma once

#include "../shaders/ShaderProgram.h"
#include "../../game/Camera.h"
#include "../lights/AmbientLight.h"
#include "../lights/Sun.h"
#include "Entity.h"
#include "StaticEntity.h"
#include "AnimatedEntity.h"
#include "../renderer/Renderer.h"

class EntityRenderer : public Renderer {

private:
    ShaderProgram staticProgram;
    ShaderProgram animatedProgram;

    static void render(ShaderProgram & program, Camera & camera, AmbientLight & ambient, Sun & sun, std::vector<Entity *> & entities);

public:
    EntityRenderer();

    void render(Camera & camera, AmbientLight & ambient, Sun & sun, const std::vector<Renderable *> & entities) override;

};