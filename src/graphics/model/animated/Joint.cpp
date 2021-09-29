#include "Joint.h"
#include "../static/StaticModelCache.h"

#include <utility>

Joint::Joint(std::string name, int id, std::vector<Joint *>  children, Mat4 &localTransformation) : name(std::move(name)), id(id), children(std::move(children)), localTransformation(localTransformation), model(StaticModelCache::get("res/models/sphere.dae")) {}

const std::string &Joint::getName() const {
    return name;
}

int Joint::getId() const {
    return id;
}

const std::vector<Joint *> &Joint::getChildren() const {
    return children;
}

Mat4 &Joint::getDefaultTransformation() {
    return localTransformation;
}

void Joint::initWorldTransformation(Mat4 parentTransform) {
    worldTransformation = parentTransform * localTransformation;
    animatedTransform = worldTransformation * inverseBindMatrix;

    for (auto & child : children) {
        child->initWorldTransformation(worldTransformation);
    }
}

void Joint::calculateAnimatedTransformation(Mat4 &currentWorldTransformation) {
    worldTransformation = currentWorldTransformation;
    animatedTransform = currentWorldTransformation * inverseBindMatrix;
}

void Joint::loadTransformation(ShaderProgram & shaderProgram) {
    std::string attributeName = "boneMatrices[" + std::to_string(id) + "]";
    shaderProgram.set(attributeName.c_str(), animatedTransform);

    for (auto & child : children) {
        child->loadTransformation(shaderProgram);
    }
}

void Joint::render(ShaderProgram &shaderProgram) {
    shaderProgram.set("model", worldTransformation);
    model->render(shaderProgram);
}

void Joint::setInverseBindMatrix(Mat4 & inverseBindMatrix) {
    this->inverseBindMatrix = inverseBindMatrix;
}

std::vector<Joint> Joint::getJoints() {
    std::vector<Joint> joints;
    joints.emplace_back(*this);
    for (auto & child : children) {
        joints.emplace_back(*child);
    }
    return joints;
}
