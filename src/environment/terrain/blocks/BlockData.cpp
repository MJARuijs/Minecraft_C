#include "BlockData.h"

BlockData::BlockData(BlockType::Type type, Vec3 position) : type(type), position(position) {}

BlockType::Type BlockData::getType() const {
    return type;
}

const Vec3 &BlockData::getPosition() const {
    return position;
}