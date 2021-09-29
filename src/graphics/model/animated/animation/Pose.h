#pragma once

#include <map>
#include "../JointTransformation.h"

class Pose {

private:
    std::map<std::string, JointTransformation> jointTransformations;

public:
    explicit Pose(std::map<std::string, JointTransformation> jointTransformations);
    Pose() = default;

    std::map<std::string, JointTransformation> getJointTransformations();
};