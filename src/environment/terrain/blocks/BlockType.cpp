#include "BlockType.h"
#include "../FaceTextures.h"

std::map<BlockType::Type, std::vector<int>> BlockType::textureIndexCache = {};
std::map<BlockType::Type, std::vector<int>> BlockType::normalIndexCache = {};
std::map<BlockType::Type, std::vector<int>> BlockType::specularIndexCache = {};

int BlockType::getTextureIndex(BlockType::Type type, Face::FaceDirection direction) {
    if (textureIndexCache.find(type) != textureIndexCache.end()) {
        return textureIndexCache[type][direction];
    }

    textureIndexCache[type] = getTextureIndices(type, COLOR_MAP);
    return textureIndexCache[type][direction];
}

int BlockType::getNormalIndex(BlockType::Type type, Face::FaceDirection direction) {
    if (normalIndexCache.find(type) != normalIndexCache.end()) {
        return normalIndexCache[type][direction];
    }

    normalIndexCache[type] = getTextureIndices(type, NORMAL_MAP);

    return normalIndexCache[type][direction];
}

int BlockType::getSpecularIndex(BlockType::Type type, Face::FaceDirection direction) {
    if (specularIndexCache.find(type) != specularIndexCache.end()) {
        return specularIndexCache[type][direction];
    }

    specularIndexCache[type] = getTextureIndices(type, SPECULAR_MAP);

    return specularIndexCache[type][direction];
}

std::vector<int> BlockType::getTextureIndices(BlockType::Type blockType, TextureMapType textureMapType) {
    std::vector<int> indices;
    std::vector<FaceMaterial> materials = getFaceMaterials(blockType);

    FaceMaterial * generalTexture;
    for (auto & material : materials) {
        if (material.getSide() == nullptr) {
            generalTexture = &material;
            break;
        }
    }

    if (generalTexture != nullptr) {
        int textureIndex = -1;
        if (textureMapType == COLOR_MAP) {
            textureIndex = FaceTextures::getTextureIndex(generalTexture->getTexturePath());
        } else if (textureMapType == NORMAL_MAP) {
            textureIndex = FaceTextures::getNormalIndex(generalTexture->getTexturePath());
        } else if (textureMapType == SPECULAR_MAP) {
            textureIndex = FaceTextures::getSpecularIndex(generalTexture->getTexturePath());
        }

        for (int i = 0; i < 6; i++) {
            indices.emplace_back(textureIndex);
        }
    } else {
        for (int i = 0; i < 6; i++) {
            indices.emplace_back(-1);
        }
    }

    for (auto & material : materials) {
        if (material.getSide() == nullptr) {
            continue;
        }

        if (textureMapType == COLOR_MAP) {
            indices[*material.getSide()] = FaceTextures::getTextureIndex(material.getTexturePath());
        } else if (textureMapType == NORMAL_MAP) {
            indices[*material.getSide()] = FaceTextures::getNormalIndex(material.getTexturePath());
        } else if (textureMapType == SPECULAR_MAP) {
            indices[*material.getSide()] = FaceTextures::getSpecularIndex(material.getTexturePath());
        }
    }

    return indices;
}

std::vector<FaceMaterial> BlockType::getFaceMaterials(BlockType::Type type) {
    switch (type) {
        case GRASS:
            return {
                FaceMaterial("grass_block_side"),
                FaceMaterial("grass_block_top", Face::TOP),
                FaceMaterial("dirt", Face::BOTTOM)
            };
        case DIRT:
            return {
                FaceMaterial("dirt")
            };
        case STONE:
            return {
                FaceMaterial("stone")
            };
        case BEDROCK:
            return {
                FaceMaterial("bedrock")
            };
        case SAND:
            return {
                FaceMaterial("sand")
            };
        case DIAMOND_ORE:
            return {
                FaceMaterial("diamond_ore")
            };
        case COBBLE_STONE:
            return {
                FaceMaterial("cobble_stone")
            };
    }
}
