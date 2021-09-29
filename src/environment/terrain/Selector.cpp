#include "Selector.h"
#include "../../util/FloatUtils.h"

bool Selector::getSelected(std::vector<Renderable*> &chunks, Camera &camera, Vec3 position, std::pair<Vec3, Face::FaceDirection> & selectedBlock) {
    Vec4 clipCoordinates(0, 0, -1, 1);
    Vec4 eyeSpace = camera.projectionMatrix.inverse() * clipCoordinates;
    eyeSpace.z = -1.0f;
    eyeSpace.w = 0.0f;

    Vec3 rayDirection = (camera.viewMatrix().inverse() * eyeSpace).xyz().unit();

    std::vector<Vec3> nearbyBlocks;

    for (auto & chunk : chunks) {
        for (auto & block : reinterpret_cast<Chunk*>(chunk)->getBlocksNearPosition(position, MAX_DISTANCE)) {
            nearbyBlocks.emplace_back(block);
        }
    }

    float smallestDistance = std::numeric_limits<float>::max();
    Vec3 selectedPoint;
//    Vec3 selectedBlock;

    for (auto & block : nearbyBlocks) {
        Vec3 * hitPoint = determineBlockHit(block, position, rayDirection);
        if (!hitPoint) {
            continue;
        }

        float distance = (*hitPoint - position).length();
        if (distance < smallestDistance) {
            smallestDistance = distance;
            selectedBlock.first = block;
            selectedPoint = *hitPoint;
        }
    }

    if (smallestDistance == std::numeric_limits<float>::max()) {
        return false;
    }

    selectedBlock.second = determineFace(selectedBlock.first, selectedPoint);
//    Face::FaceDirection selectedFace
//    std::pair<Vec3, int> pair(selectedBlock, 0);
    return true;
}

Vec3 *Selector::determineBlockHit(Vec3 min, Vec3 position, Vec3 rayDirection) {
    Vec3 max = min + Vec3(1, 1, 1);
    float tMin = std::numeric_limits<float>::min();
    float tMax = std::numeric_limits<float>::max();

    for (int i = 0; i < 3; i++) {
        float ood = 1.0f / rayDirection[i];
        float t1 = (min[i] - position[i]) * ood;
        float t2 = (max[i] - position[i]) * ood;

        if (t1 > t2) {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        tMin = std::max(tMin, t1);
        tMax = std::min(tMax, t2);

        if (tMin > tMax) {
            return nullptr;
        }
    }

    return new Vec3(position + rayDirection * tMin);
}

Face::FaceDirection Selector::determineFace(Vec3 blockPosition, Vec3 hitPoint) {
    if (FloatUtils::compare(blockPosition.x, hitPoint.x)) {
        return Face::LEFT;
    }
    if (FloatUtils::compare(blockPosition.x + 1.0f, hitPoint.x)) {
        return Face::RIGHT;
    }
    if (FloatUtils::compare(blockPosition.y, hitPoint.y)) {
        return Face::BOTTOM;
    }
    if (FloatUtils::compare(blockPosition.y + 1.0f, hitPoint.y)) {
        return Face::TOP;
    }
    if (FloatUtils::compare(blockPosition.z, hitPoint.z)) {
        return Face::BACK;
    }
    if (FloatUtils::compare(blockPosition.z + 1.0f, hitPoint.z)) {
        return Face::FRONT;
    }
    throw std::runtime_error("Point " + hitPoint.toString() + " does not belong on block: " + blockPosition.toString());
}
