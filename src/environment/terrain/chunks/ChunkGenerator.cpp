#include <thread>
#include "ChunkGenerator.h"

BlockType::Type ChunkGenerator::determineBlockType(int y, int maxY, Biome::BiomeType biome) {

    BlockType::Type blockType = BlockType::STONE;
    int typeHeight = 0;
    for (auto & type : Biome::getBlocks(biome)) {
        if (y > maxY - type.second - typeHeight) {
            blockType = type.first;
            break;
        }
        typeHeight += type.second;
    }

    return blockType;
}

void ChunkGenerator::addFaceData(int x, int height, int z, Face::FaceDirection direction, BlockType::Type type) {
    std::vector<float> vertices = Face::getVertices(direction);

    for (int i = 0; i < vertices.size(); i += 3) {
        positionData.emplace_back(vertices[i] + (float)x);
        positionData.emplace_back(vertices[i + 1] + (float)height);
        positionData.emplace_back(vertices[i + 2] + (float)z);
        textureIndices.emplace_back(BlockType::getTextureIndex(type, direction));
        normalIndices.emplace_back(BlockType::getNormalIndex(type, direction));
        specularIndices.emplace_back(BlockType::getSpecularIndex(type, direction));

        vertexCount += 1;
    }
}

void ChunkGenerator::addFacesBelow(int x, int height, int z, int heightDifference, Face::FaceDirection face, Biome::BiomeType biome) {
    if (heightDifference > 0) {
        for (int y = 0; y < heightDifference - 1; y ++) {
            BlockType::Type extraBlockType = determineBlockType(height - y - 1, height, biome);
            addFaceData(x, height - y - 1, z, face, extraBlockType);
        }
    }
}

std::vector<BlockData> ChunkGenerator::addBlocksBelow(int x, int z, Biome::BiomeType biome) {
    int height = get(x, z);
    int leftHeight = get(x - 1, z);
    int rightHeight = get(x + 1, z);
    int frontHeight = get(x, z + 1);
    int backHeight = get(x, z - 1);

    int leftDifference = height - leftHeight;
    int rightDifference = height - rightHeight;
    int frontDifference = height - frontHeight;
    int backDifference = height - backHeight;

    int largestDifference = std::max(std::max(std::max(leftDifference, rightDifference), frontDifference), backDifference);

    if (largestDifference <= 0) {
        return std::vector<BlockData>();
    }

    std::vector<BlockData> extraBlocks;

    for (int y = 0; y < largestDifference - 1; y++) {
        BlockType::Type type = determineBlockType(height - y - 1, height, biome);
        Vec3 position = Vec3(x + chunkX, height - y - 1, z + chunkZ);
        positions.emplace_back(position);
        extraBlocks.emplace_back(type, position);
    }

    return extraBlocks;
}

int ChunkGenerator::get(int x, int z) {
    if (x < 0 || z < 0 || x >= CHUNK_SIZE || z >= CHUNK_SIZE) {
        return (int)noise.get((x + chunkX), (z + chunkZ)) + TERRAIN_HEIGHT;
    }
    if (heights[x][z] == 0) {
        heights[x][z] = (int)noise.get((x + chunkX), (z + chunkZ)) + TERRAIN_HEIGHT;
    }
    return heights[x][z];
}

Chunk ChunkGenerator::generate(int chunkX, int chunkZ, Biome::BiomeType biome, long seed) {
    this->chunkX = chunkX - HALF_CHUNK_SIZE;
    this->chunkZ = chunkZ - HALF_CHUNK_SIZE;
    noise = Noise(Biome::getOctaves(biome), Biome::getAmplitude(biome), Biome::getSmoothness(biome), seed);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            heights[x][z] = 0;
        }
    }

    std::vector<BlockData> blockData;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            int worldX = chunkX + x - HALF_CHUNK_SIZE;
            int worldZ = chunkZ + z - HALF_CHUNK_SIZE;
            int height = get(x, z);

            BlockType::Type blockType = determineBlockType(height, height, biome);

            int leftHeight = get(x - 1, z);
            int rightHeight = get(x + 1, z);
            int frontHeight = get(x, z + 1);
            int backHeight = get(x, z - 1);

            addFaceData(worldX, height, worldZ, Face::TOP, blockType);
            if (height == 0) {
                addFaceData(worldX, height, worldZ, Face::BOTTOM, blockType);
            }

            if (leftHeight < height) addFaceData(worldX, height, worldZ, Face::LEFT, blockType);
            if (rightHeight < height) addFaceData(worldX, height, worldZ, Face::RIGHT, blockType);
            if (backHeight < height) addFaceData(worldX, height, worldZ, Face::BACK, blockType);
            if (frontHeight < height) addFaceData(worldX, height, worldZ, Face::FRONT, blockType);

            int leftDifference = height - leftHeight;
            int rightDifference = height - rightHeight;
            int frontDifference = height - frontHeight;
            int backDifference = height - backHeight;

            addFacesBelow(worldX, height, worldZ, backDifference, Face::BACK, biome);
            addFacesBelow(worldX, height, worldZ, frontDifference, Face::FRONT, biome);
            addFacesBelow(worldX, height, worldZ, leftDifference, Face::LEFT, biome);
            addFacesBelow(worldX, height, worldZ, rightDifference, Face::RIGHT, biome);

            Vec3 position(worldX, height, worldZ);
            positions.emplace_back(position);
            blockData.emplace_back(blockType, position);

            std::vector<BlockData> blocksBelow = addBlocksBelow(x, z, biome);
            for (auto & blockBelow : blocksBelow) {
                blockData.emplace_back(blockBelow);
            }
        }
    }

    Chunk chunk(chunkX, chunkZ, biome, blockData, positionData, textureIndices, normalIndices, specularIndices, vertexCount);

    std::thread t([&] {
        std::vector<BlockData> newBlocks;
        for (int x = 0; x < CHUNK_SIZE; x++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                int worldX = chunkX + x - HALF_CHUNK_SIZE;
                int worldZ = chunkZ + z - HALF_CHUNK_SIZE;

                int height = get(x, z);

                for (int y = 0; y < height; y++) {
                    Vec3 position(worldX, y, worldZ);
                    bool containsPosition = std::any_of(positions.begin(), positions.end(), [&](Vec3 pos) {
                        return pos == position;
                    });

                    if (containsPosition) {
                        continue;
                    }

                    BlockType::Type blockType = determineBlockType(y, height, biome);
                    newBlocks.emplace_back(blockType, position);
                }
            }
        }
        chunk.add(newBlocks);
    });

    t.join();

    return chunk;
}
