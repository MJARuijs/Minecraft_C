#include <thread>
#include "ChunkManager.h"
#include "ChunkGenerator.h"
#include "../FaceTextures.h"

ChunkManager::ChunkManager(int x, int z) : currentX(floor((x + HALF_CHUNK_SIZE) / CHUNK_SIZE)), currentZ(floor((z + HALF_CHUNK_SIZE) / CHUNK_SIZE)), maxDistance(0), preGenerateDistance(0), renderDistance(0) {
    FaceTextures::load("res/textures/blocks");
    update();
}

int ChunkManager::getRenderDistance() const {
    return renderDistance;
}

void ChunkManager::update() {
    int i = 0;

    for (auto & chunk : chunks) {
        int xDistance = abs(chunk.getX() - currentX * CHUNK_SIZE);
        int zDistance = abs(chunk.getZ() - currentZ * CHUNK_SIZE);
        if (xDistance > maxDistance * CHUNK_SIZE || zDistance > maxDistance * CHUNK_SIZE) {
            chunks.erase(chunks.begin() + i);
        }
        i++;
    }

    int distance = preGenerateDistance * CHUNK_SIZE;
    for (int x = -distance; x <= distance; x += CHUNK_SIZE) {
        for (int z = -distance; z <= distance; z += CHUNK_SIZE) {
            std::thread t([&]() {
                 generate(currentX * CHUNK_SIZE + x, currentZ * CHUNK_SIZE + z);
            });
            t.join();
        }
    }
}

void ChunkManager::generate(int x, int z) {
    bool chunkExists = std::any_of(chunks.begin(), chunks.end(), [&](Chunk & chunk) {
        return chunk.getX() == x && chunk.getZ() == z;
    });

    if (!chunkExists) {
        chunks.emplace_back(ChunkGenerator().generate(x, z, Biome::PLANES, 0));
    }
}

void ChunkManager::setRenderDistance(int renderDistance) {
    if (renderDistance < 0) {
        return;
    }

    this->renderDistance = renderDistance;

    if (preGenerateDistance < renderDistance) {
        preGenerateDistance = renderDistance;
    }

    if (maxDistance < renderDistance) {
        maxDistance = renderDistance;
    }

    update();
}

void ChunkManager::updatePosition(const Vec3 &position) {
    int chunkX = std::floor((position.x + (float)HALF_CHUNK_SIZE) / CHUNK_SIZE);
    int chunkZ = std::floor((position.z + (float)HALF_CHUNK_SIZE) / CHUNK_SIZE);

    if (chunkX != currentX || chunkZ != currentZ) {
        currentX = chunkX;
        currentZ = chunkZ;

        std::thread t([&] {
            update();
        });
        t.join();
    }
}

std::vector<Renderable*> ChunkManager::determineVisibleChunks() {
    std::vector<Renderable*> visibleChunks;
    for (int x = (currentX - renderDistance) * CHUNK_SIZE; x <= (currentX + renderDistance) * CHUNK_SIZE; x += CHUNK_SIZE) {
        for (int z = (currentZ - renderDistance) * CHUNK_SIZE; z <= (currentZ + renderDistance) * CHUNK_SIZE; z += CHUNK_SIZE) {
            Chunk * c = nullptr;

            for (auto & chunk : chunks) {
                if (chunk.getX() == x && chunk.getZ() == z) {
                    c = &chunk;
                    break;
                }
            }

            if (c) {
                visibleChunks.emplace_back(c);
            }
        }
    }
    return visibleChunks;
}
