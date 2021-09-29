#pragma once

#include "../../math/vectors/Vec3.h"
#include "chunks/Face.h"
#include "chunks/Chunk.h"
#include "../../game/Camera.h"

#define MAX_DISTANCE 8.0f

class Selector {

private:
    static Vec3 * determineBlockHit(Vec3 min, Vec3 position, Vec3 rayDirection);
    static Face::FaceDirection determineFace(Vec3 blockPosition, Vec3 hitPoint);

public:
    static bool getSelected(std::vector<Renderable*> & chunks, Camera & camera, Vec3 position, std::pair<Vec3, Face::FaceDirection> & selectedBlock);
};