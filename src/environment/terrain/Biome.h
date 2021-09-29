#pragma once

#include "../../math/Color.h"
#include "blocks/BlockData.h"

class Biome {

public:
    enum BiomeType {
        PLANES,
        HILLS,
        MOUNTAINS,
        DESERT
    };

    static int getOctaves(BiomeType type);
    static int getAmplitude(BiomeType type);
    static int getSmoothness(BiomeType type);
    static Color getOverlayColor(BiomeType type);
    static std::vector<std::pair<BlockType::Type, int>> getBlocks(BiomeType type);

    int getOctaves();
    int getAmplitude();
    Color getOverlayColor();
    std::vector<std::pair<BlockType::Type, int>> getBlocks();

private:
    BiomeType type;
};