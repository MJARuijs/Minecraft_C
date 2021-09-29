#pragma once

#include <vector>
#include "../../../math/vectors/Vec3.h"

class Face {

public:
    enum FaceDirection {
        FRONT = 0,
        BACK,
        TOP,
        BOTTOM,
        RIGHT,
        LEFT
    };

    explicit Face(FaceDirection direction);

    static Vec3 getNormal(FaceDirection direction);
    static FaceDirection getOpposite(FaceDirection direction);
    static std::vector<float> getVertices(FaceDirection direction);
    static std::vector<FaceDirection> getValues();

    std::vector<float> getVertices();
//    std::vector<FaceDirection> getValues();

private:
    static std::vector<FaceDirection> values;
    FaceDirection direction;

};