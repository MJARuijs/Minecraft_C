#pragma once

#include "Entity.h"

class StaticEntity : public Entity {

private:
//    StaticModel * model;
//    Mat4 transformation;

public:
    StaticEntity(StaticModel * model, Mat4 transformation);
    explicit StaticEntity(StaticModel * model);

    void render(ShaderProgram & shaderProgram) override;

};