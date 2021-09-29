#include "Face.h"

Face::Face(Face::FaceDirection direction) : direction(direction) {}

std::vector<Face::FaceDirection> Face::values = {
        FRONT,
        BACK,
        TOP,
        BOTTOM,
        RIGHT,
        LEFT
};

std::vector<float> Face::getVertices() {
    return getVertices(direction);
}

std::vector<Face::FaceDirection> Face::getValues() {
    return values;
}

Vec3 Face::getNormal(Face::FaceDirection direction) {
    switch (direction) {
        case FRONT:
            return Vec3(0, 0, 1);
        case BACK:
            return Vec3(0, 0, -1);
        case TOP:
            return Vec3(0, 1, 0);
        case BOTTOM:
            return Vec3(0, -1, 0);
        case RIGHT:
            return Vec3(1, 0, 0);
        case LEFT:
            return Vec3(-1, 0, 0);
    }
    return Vec3();
}

Face::FaceDirection Face::getOpposite(Face::FaceDirection direction) {
    switch (direction) {
        case FRONT:
            return BACK;
        case BACK:
            return FRONT;
        case TOP:
            return BOTTOM;
        case BOTTOM:
            return TOP;
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
    }
}

std::vector<float> Face::getVertices(Face::FaceDirection direction) {
    switch (direction) {
        case FRONT:
            return {
                    0.0f, 1.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 1.0f
            };
        case BACK:
            return {
                    1.0f, 1.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f
            };
        case TOP:
            return {
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 0.0f
            };
        case BOTTOM:
            return {
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 1.0f
            };
        case RIGHT:
            return {
                    1.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 0.0f
            };
        case LEFT:
            return {
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 1.0f
            };
    }
}
