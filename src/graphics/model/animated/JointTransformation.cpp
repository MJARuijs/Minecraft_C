#include "JointTransformation.h"

JointTransformation::JointTransformation(Vec3 position, Quaternion rotation, Vec3 &scale) : position(position), rotation(rotation), scale(scale) {}

JointTransformation::JointTransformation(Vec3 position, Quaternion rotation) : position(position), rotation(rotation), scale(1.0f, 1.0f, 1.0f) {}

Mat4 JointTransformation::getTransformationMatrix() {
    return Mat4().scale(scale).rotate(rotation).translate(position);
}

JointTransformation::JointTransformation(): position(), rotation(), scale() {}

JointTransformation JointTransformation::interpolate(JointTransformation a, JointTransformation b, float progress) {
    Vec3 position = (b.position - a.position) * progress + a.position;
    Quaternion rotation = Quaternion::interpolate(a.rotation, b.rotation, progress);
    Vec3 scale = (b.scale - a.scale) * progress + a.scale;
    return JointTransformation(position, rotation, scale);
}


