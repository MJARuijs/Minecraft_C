#pragma once

#include "../Shape.h"

class StaticModel {

private:
    std::vector<Shape*> shapes;

public:
    explicit StaticModel(std::vector<Shape*> shapes);
    ~StaticModel();

    virtual void render(ShaderProgram & shaderProgram);

};