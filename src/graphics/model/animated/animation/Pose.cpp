#include "Pose.h"

#include <utility>
#include <iostream>

Pose::Pose(std::map<std::string, JointTransformation> jointTransformations) : jointTransformations(std::move(jointTransformations)) {}

std::map<std::string, JointTransformation> Pose::getJointTransformations() {
    return jointTransformations;
}
