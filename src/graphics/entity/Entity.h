#pragma once

#include "../model/static/StaticModel.h"
#include "../renderer/Renderable.h"

class Entity : public Renderable {

public:
    enum Type {
        STATIC,
        ANIMATED
    };

    [[nodiscard]] Type getType() const;

    void render(ShaderProgram & shaderProgram) override;

protected:
    explicit Entity(Type type, StaticModel * model, Mat4 transformation);
    Entity(Type type, StaticModel * model);

    Mat4 transformation;
    StaticModel * model;

private:
    Type type;

};