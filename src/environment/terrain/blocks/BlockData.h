#pragma once

#include "../../../math/vectors/Vec3.h"
#include "FaceMaterial.h"
#include "BlockType.h"

class BlockData {

public:
    BlockData(BlockType::Type type, Vec3 position);

    [[nodiscard]] BlockType::Type getType() const;
    [[nodiscard]] const Vec3 & getPosition() const;

private:
    BlockType::Type type;
    Vec3 position;
};