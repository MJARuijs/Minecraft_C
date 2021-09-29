#pragma once

#include <cmath>
#include "../math/vectors/Vec3.h"
#include "../math/matrices/Mat4.h"

class Camera {

private:
    Vec3 position;
    Vec3 rotation;
    float fieldOfView;
    float aspectRatio;
    float zNear;
    float zFar;

public:
    Camera(const Vec3 & position, const Vec3 & rotation, float fieldOfView, float aspectRatio, float zNear, float zFar);
    explicit Camera(float aspectRatio);

    Mat4 projectionMatrix = Mat4({
            1.0f / (aspectRatio * (float)tan((M_PI / 180.0f) * fieldOfView / 2.0f)), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / (float)tan((M_PI / 180.0f) * fieldOfView / 2.0f), 0.0f, 0.0f,
            0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -(2.0f * zFar * zNear) / (zFar - zNear),
            0.0f, 0.0f, -1.0f, 0.0f
    });

    float & getFarPlane();

    void setPosition(const Vec3 &position);

    void setRotation(const Vec3 &rotation);

    Mat4 viewMatrix();

    [[nodiscard]] Vec3 getPosition();
};