#pragma once

#include "../../../math/vectors/Vec3.h"
#include "../../../math/Quaternion.h"
#include "../../../math/matrices/Mat4.h"

class JointTransformation {

public:
    JointTransformation(Vec3 position, Quaternion rotation, Vec3 & scale);
    JointTransformation(Vec3 position, Quaternion rotation);
    JointTransformation();

    Mat4 getTransformationMatrix();

    static JointTransformation interpolate(JointTransformation a, JointTransformation b, float progress);

    Vec3 position;
    Quaternion rotation;
    Vec3 scale;
};