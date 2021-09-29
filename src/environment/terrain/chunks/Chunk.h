#pragma once

#include <vector>
#include <valarray>
#include "../blocks/BlockData.h"
#include "../Biome.h"
#include "../../../graphics/shaders/ShaderProgram.h"
#include "ChunkMesh.h"
#include "../../../graphics/renderer/Renderable.h"

#define POSITION_INSTANCE_SIZE 18
#define TEXTURE_INSTANCE_SIZE 6

class Chunk : public Renderable {

    union FloatBuffer {
        float value;
        char data[sizeof(float)];
    };

    union IntBuffer {
        int value;
        char data[sizeof(int)];
    };

private:
    int x;
    int z;

    Biome::BiomeType biome;

    std::vector<BlockData> blocks;
    std::vector<BlockData> hiddenBlocks;

    std::vector<float> positionData;
    std::vector<int> textureIndices;
    std::vector<int> normalIndices;
    std::vector<int> specularIndices;

    int vertexCount;
    bool initialized;

    ChunkMesh * mesh;

    void init();
    void bufferData(char * data);
    void updateMesh();

    bool containsVisibleBlock(Vec3 position);
    bool containsHiddenBlock(Vec3 position);

    BlockData * getVisibleBlock(Vec3 position);
    BlockData getAndRemoveHiddenBlock(Vec3 position);

    void addFaceData(BlockData block, Face::FaceDirection direction);
    void removeFaceData(Vec3 position, Face::FaceDirection direction);
    void removeFaceData(int index);
    std::vector<int> getIndices(Vec3 position, Face::FaceDirection direction);
    bool getIndicesHelper(Vec3 position, Face::FaceDirection direction, int i);

public:
    Chunk(int x, int z, Biome::BiomeType biome,
          std::vector<BlockData> blocks,
          std::vector<float> positionData,
          std::vector<int> textureIndices,
          std::vector<int> normalIndices,
          std::vector<int> specularIndices,
          int vertexCount);

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getZ() const;

    void render(ShaderProgram & shaderProgram) override;
    void update();
    void stopBreaking();

    void addBlock(Vec3 position, BlockType::Type type);
    void removeBlock(Vec3 position);

    bool containsBlock(Vec3 position);
    void add(const std::vector<BlockData> & blockData);
    std::vector<Vec3> getBlocksNearPosition(Vec3 position, float maxDistance);

};