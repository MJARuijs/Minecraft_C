#pragma once

#include <vector>
#include "../../../math/vectors/Vec3.h"
#include "Chunk.h"
#include "../../../math/Noise.h"

#define CHUNK_SIZE 16
#define HALF_CHUNK_SIZE CHUNK_SIZE / 2
#define TERRAIN_HEIGHT 15

class ChunkGenerator {

private:
    int heights[16][16];
    std::vector<Vec3> positions;
    Noise noise;

    int chunkX;
    int chunkZ;

    std::vector<float> positionData;
    std::vector<int> textureIndices;
    std::vector<int> normalIndices;
    std::vector<int> specularIndices;

    int vertexCount;

    int get(int x, int z);

    void addFaceData(int x, int height, int z, Face::FaceDirection direction, BlockType::Type type);
    void addFacesBelow(int x, int height, int z, int heightDifference, Face::FaceDirection face, Biome::BiomeType biome);
    static BlockType::Type determineBlockType(int y, int maxY, Biome::BiomeType biome);
    std::vector<BlockData> addBlocksBelow(int x, int z, Biome::BiomeType biome);

public:
    Chunk generate(int chunkX, int chunkZ, Biome::BiomeType biome, long seed);

};