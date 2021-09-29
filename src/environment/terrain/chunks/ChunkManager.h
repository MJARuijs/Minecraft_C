#pragma once

#include <vector>
#include "Chunk.h"
#include "../../../devices/input/Keyboard.h"

class ChunkManager {

private:
    int currentX;
    int currentZ;

    int maxDistance;
    int preGenerateDistance;
    int renderDistance;

    std::vector<Chunk> chunks;

    void update();
    void generate(int x, int z);

public:
    ChunkManager(int x, int z);

    [[nodiscard]] int getRenderDistance() const;
    void setRenderDistance(int renderDistance);

    void updatePosition(const Vec3 & position);
    std::vector<Renderable*> determineVisibleChunks();
};