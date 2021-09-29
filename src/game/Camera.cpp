#include "Camera.h"

Camera::Camera(const Vec3 &position, const Vec3 &rotation, float fieldOfView, float aspectRatio, float zNear,
               float zFar) : position(position), rotation(rotation), fieldOfView(fieldOfView), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar) {}

Camera::Camera(float aspectRatio) : position(), rotation(), fieldOfView(70.0f), aspectRatio(aspectRatio), zNear(0.01f), zFar(1000.0f) {}

Vec3 Camera::getPosition() {
    return position;
}

float &Camera::getFarPlane() {
    return zFar;
}

Mat4 Camera::viewMatrix() {
    return Mat4().translate(-position).rotate(rotation);
}

void Camera::setPosition(const Vec3 &position) {
    Camera::position = position;
}

void Camera::setRotation(const Vec3 &rotation) {
    Camera::rotation = rotation;
}
