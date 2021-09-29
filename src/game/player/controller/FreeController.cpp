#include "FreeController.h"

#include <cmath>

FreeController::FreeController(const Vec3 &position) : position(position), rotation() {}

void FreeController::update(Camera & camera, Mouse &mouse, Keyboard &keyboard, float delta) {
    Vec3 translation;

    if (keyboard.keyDown(GLFW_KEY_W)) {
        translation.z += 1.0f;
    }
    if (keyboard.keyDown(GLFW_KEY_S)) {
        translation.z -= 1.0f;
    }
    if (keyboard.keyDown(GLFW_KEY_A)) {
        translation.x += 1.0f;
    }
    if (keyboard.keyDown(GLFW_KEY_D)) {
        translation.x -= 1.0f;
    }
    if (keyboard.keyDown(GLFW_KEY_SPACE)) {
        translation.y -= 1.0f;
    }
    if (keyboard.keyDown(GLFW_KEY_LEFT_SHIFT)) {
        translation.y += 1.0f;
    }

    if (translation.length() > 0.0f) {
        Mat4 rotationMatrix = Mat4().rotateY(-rotation.y);
        position += (rotationMatrix * (-translation.unit() * delta * MOVE_SPEED)).xyz();
    }

    rotation.x += mouse.delta.y * MOUSE_SPEED;
    rotation.x = std::fmin(std::fmax(-(float)M_PI_2, rotation.x), (float)M_PI_2);
    rotation.y += mouse.delta.x * MOUSE_SPEED;

    camera.setPosition(position);
    camera.setRotation(rotation);
}
