#include "StaticModel.h"

StaticModel::StaticModel(std::vector<Shape*> shapes) : shapes(std::move(shapes)) {}

void StaticModel::render(ShaderProgram &shaderProgram) {
    for (auto & shape : shapes) {
        shape->render(shaderProgram);
    }
}

StaticModel::~StaticModel() {
    for (auto shape : shapes) {
        delete shape;
    }
}
