#include "Biome.h"

Color Biome::getOverlayColor() {
    return getOverlayColor(type);
}

std::vector<std::pair<BlockType::Type, int>> Biome::getBlocks() {
    return getBlocks(type);
}

int Biome::getOctaves() {
    return getOctaves(type);
}

int Biome::getAmplitude() {
    return getAmplitude(type);
}

std::vector<std::pair<BlockType::Type, int>> Biome::getBlocks(BiomeType type) {
    switch (type) {
        case PLANES:
        case HILLS:
            return {
                std::pair(BlockType::GRASS, 1),
                std::pair(BlockType::DIRT, 3)
            };
        case MOUNTAINS:
            return {
                std::pair(BlockType::STONE, 1)
            };
        case DESERT:
            return {
                std::pair(BlockType::SAND, 3)
            };
    }
    return std::vector<std::pair<BlockType::Type, int>>();
}

Color Biome::getOverlayColor(Biome::BiomeType type) {
    switch (type) {
        case PLANES:
        case HILLS:
        case MOUNTAINS:
            return Color(50, 200, 50);
        case DESERT:
            return Color();
    }
    return Color();
}

int Biome::getOctaves(Biome::BiomeType type) {
    switch (type) {
        case PLANES:
        case HILLS:
            return 1;
        case MOUNTAINS:
            return 3;
        case DESERT:
            return 1;
    }
    return -1;
}

int Biome::getAmplitude(Biome::BiomeType type) {
    switch (type) {
        case PLANES:
            return 3;
        case HILLS:
            return 10;
        case MOUNTAINS:
            return 20;
        case DESERT:
            return 3;
    }
    return -1;
}

int Biome::getSmoothness(Biome::BiomeType type) {
    switch (type) {
        case PLANES:
        case HILLS:
            return 3;
        case MOUNTAINS:
            return 5;
        case DESERT:
            return 3;
    }
    return -1;
}
