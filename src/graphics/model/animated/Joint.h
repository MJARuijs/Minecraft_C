#pragma once

#include <string>
#include <vector>
#include "../../../math/matrices/Mat4.h"
#include "../../shaders/ShaderProgram.h"
#include "../static/StaticModel.h"

class Joint {

private:
    std::string name;
    int id;
    std::vector<Joint *> children;

    Mat4 localTransformation;
    Mat4 worldTransformation;
    Mat4 inverseBindMatrix;
    Mat4 animatedTransform;
    StaticModel * model;

public:
    Joint(std::string name, int id, std::vector<Joint *> children, Mat4 & localTransformation);

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::vector<Joint *> &getChildren() const;

    std::vector<Joint> getJoints();

    Mat4 & getDefaultTransformation();

    void initWorldTransformation(Mat4 parentTransform);
    void calculateAnimatedTransformation(Mat4 & currentWorldTransformation);

    void loadTransformation(ShaderProgram & shaderProgram);
    void render(ShaderProgram & shaderProgram);

    void setInverseBindMatrix(Mat4 &inverseBindMatrix);
};