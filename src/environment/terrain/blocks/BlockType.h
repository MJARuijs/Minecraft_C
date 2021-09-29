#pragma once

#include <vector>
#include <map>
#include "FaceMaterial.h"
#include "../../../graphics/textures/TextureMapType.h"

class BlockType {

public:
    enum Type {
        GRASS,
        DIRT,
        STONE,
        COBBLE_STONE,
        BEDROCK,
        SAND,
        DIAMOND_ORE
    };

    static std::vector<FaceMaterial> getFaceMaterials(BlockType::Type type);
    static int getTextureIndex(BlockType::Type type, Face::FaceDirection direction);
    static int getNormalIndex(BlockType::Type type, Face::FaceDirection direction);
    static int getSpecularIndex(BlockType::Type type, Face::FaceDirection direction);

private:
    BlockType() = default;

    static std::map<Type, std::vector<int>> textureIndexCache;
    static std::map<Type, std::vector<int>> normalIndexCache;
    static std::map<Type, std::vector<int>> specularIndexCache;

    static std::vector<int> getTextureIndices(BlockType::Type blockType, TextureMapType textureMapType);

};

