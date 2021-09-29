#include "Chunk.h"

#include <utility>

Chunk::Chunk(int x, int z, Biome::BiomeType biome,
             std::vector<BlockData> blocks,
             std::vector<float> positionData,
             std::vector<int> textureIndices,
             std::vector<int> normalIndices,
             std::vector<int> specularIndices,
             int vertexCount) :
             x(x), z(z), biome(biome),
             blocks(std::move(blocks)),
             positionData(std::move(positionData)),
             textureIndices(std::move(textureIndices)),
             normalIndices(std::move(normalIndices)),
             specularIndices(std::move(specularIndices)),
             vertexCount(vertexCount),
             hiddenBlocks(),
             initialized(false),
             mesh(nullptr) {

}

void Chunk::init() {
    char buffer[4 * 6 * vertexCount];
    bufferData(buffer);
    mesh = new ChunkMesh(buffer, vertexCount);
    initialized = true;
}

int Chunk::getX() const {
    return x;
}

int Chunk::getZ() const {
    return z;
}

void Chunk::bufferData(char * data) {
    int j = 0;
    FloatBuffer floatBuffer = {};
    IntBuffer intBuffer = {};

    for (int i = 0; i < vertexCount * 3; i += 3) {
        floatBuffer.value = positionData[i];

        data[j++] = floatBuffer.data[0];
        data[j++] = floatBuffer.data[1];
        data[j++] = floatBuffer.data[2];
        data[j++] = floatBuffer.data[3];

        floatBuffer.value = positionData[i + 1];
        data[j++] = floatBuffer.data[0];
        data[j++] = floatBuffer.data[1];
        data[j++] = floatBuffer.data[2];
        data[j++] = floatBuffer.data[3];

        floatBuffer.value = positionData[i + 2];
        data[j++] = floatBuffer.data[0];
        data[j++] = floatBuffer.data[1];
        data[j++] = floatBuffer.data[2];
        data[j++] = floatBuffer.data[3];

        intBuffer.value = textureIndices[i / 3];
        data[j++] = intBuffer.data[0];
        data[j++] = intBuffer.data[1];
        data[j++] = intBuffer.data[2];
        data[j++] = intBuffer.data[3];

        intBuffer.value = normalIndices[i / 3];
        data[j++] = intBuffer.data[0];
        data[j++] = intBuffer.data[1];
        data[j++] = intBuffer.data[2];
        data[j++] = intBuffer.data[3];

        intBuffer.value = specularIndices[i / 3];
        data[j++] = intBuffer.data[0];
        data[j++] = intBuffer.data[1];
        data[j++] = intBuffer.data[2];
        data[j++] = intBuffer.data[3];
    }
}

void Chunk::updateMesh() {
    char buffer[4 * 6 * vertexCount];
    bufferData(buffer);
    mesh->updateInstanceData(buffer, vertexCount);
}

bool Chunk::containsVisibleBlock(Vec3 position) {
    return std::any_of(blocks.begin(), blocks.end(), [&](BlockData & block) {
        return position == block.getPosition();
    });
}

bool Chunk::containsHiddenBlock(Vec3 position) {
    return std::any_of(hiddenBlocks.begin(), hiddenBlocks.end(), [&](BlockData & block) {
        return position == block.getPosition();
    });
//    for (auto & block : hiddenBlocks) {
//        if (position == block.getPosition()) {
//            return true;
//        }
//    }
//    return false;
}

BlockData *Chunk::getVisibleBlock(Vec3 position) {
    for (auto & block : blocks) {
        if (position == block.getPosition()) {
            return &block;
        }
    }
    return nullptr;
}

BlockData Chunk::getAndRemoveHiddenBlock(Vec3 position) {
    auto blockData = std::find_if(begin(hiddenBlocks), end(hiddenBlocks), [&](BlockData & data) {
        return data.getPosition() == position;
    });

    int index = 0;
    for (auto & block : hiddenBlocks) {
        if (position == block.getPosition()) {
            break;
        }
        index++;
    }

    BlockData result(blockData->getType(), blockData->getPosition());

    hiddenBlocks.erase(hiddenBlocks.begin() + index);
    return result;
}

void Chunk::addFaceData(BlockData block, Face::FaceDirection direction) {
    std::vector<float> vertices = Face::getVertices(Face::getOpposite(direction));
    for (int i = 0; i < vertices.size(); i += 3) {
        positionData.emplace_back(block.getPosition().x + vertices[i]);
        positionData.emplace_back(block.getPosition().y + vertices[i + 1]);
        positionData.emplace_back(block.getPosition().z + vertices[i + 2]);
        textureIndices.emplace_back(BlockType::getTextureIndex(block.getType(), Face::getOpposite(direction)));
        normalIndices.emplace_back(BlockType::getNormalIndex(block.getType(), Face::getOpposite(direction)));
        specularIndices.emplace_back(BlockType::getSpecularIndex(block.getType(), Face::getOpposite(direction)));
        vertexCount += 1;
    }
}

void Chunk::render(ShaderProgram &shaderProgram) {
    shaderProgram.set("overlayColor", Biome::getOverlayColor(biome));

    if (initialized) {
        mesh->render();
    } else {
        init();
        mesh->render();
    }
}

void Chunk::addBlock(Vec3 position, BlockType::Type type) {
    blocks.emplace_back(type, position);

    for (auto & direction : Face::getValues()) {
        if (containsBlock(position + Face::getNormal(direction))) {
            removeFaceData(position + Face::getNormal(direction), Face::getOpposite(direction));
        }

        if (!containsBlock(position + Face::getNormal(direction))) {
            std::vector<float> vertices = Face::getVertices(direction);
            for (int i = 0; i < vertices.size(); i += 3) {
                positionData.emplace_back(vertices[i] + position.x);
                positionData.emplace_back(vertices[i + 1] + position.y);
                positionData.emplace_back(vertices[i + 2] + position.z);
                textureIndices.emplace_back(BlockType::getTextureIndex(type, direction));
                normalIndices.emplace_back(BlockType::getNormalIndex(type, direction));
                specularIndices.emplace_back(BlockType::getSpecularIndex(type, direction));
                vertexCount += 1;
            }
        }
    }

    updateMesh();
}

void Chunk::update() {

}

void Chunk::stopBreaking() {

}

void Chunk::removeBlock(Vec3 position) {
    int i = 0;
    for (auto & block : blocks) {
        if (position == block.getPosition()) {
            break;
        }
        i++;
    }

    blocks.erase(blocks.begin() + i);

    for (auto & direction : Face::getValues()) {
        if (!containsBlock(position + Face::getNormal(direction))) {
            removeFaceData(position, direction);
        } else {
            if (containsHiddenBlock(position + Face::getNormal(direction))) {
                BlockData block = getAndRemoveHiddenBlock(position + Face::getNormal(direction));
                blocks.emplace_back(block);
                addFaceData(block, direction);
            } else if (containsVisibleBlock(position + Face::getNormal(direction))) {
                BlockData * block = getVisibleBlock(position + Face::getNormal(direction));
                if (block) {
                    addFaceData(*block, direction);
                }
            }
        }
    }
    updateMesh();
}

bool Chunk::containsBlock(Vec3 position) {
    return containsVisibleBlock(position) || containsHiddenBlock(position);
}

void Chunk::add(const std::vector<BlockData> &blockData) {
    for (auto & block : blockData) {
        hiddenBlocks.emplace_back(block);
    }
}

void Chunk::removeFaceData(Vec3 position, Face::FaceDirection direction) {
    std::vector<int> indices = getIndices(position, direction);

    for (auto & index : indices) {
        removeFaceData(index);
    }
}

std::vector<Vec3> Chunk::getBlocksNearPosition(Vec3 position, float maxDistance) {
    std::vector<Vec3> blockPositions;
    for (auto & block : blocks) {
        if ((position - block.getPosition()).length() < maxDistance) {
            blockPositions.emplace_back(block.getPosition());
        }
    }
    return blockPositions;
}

void Chunk::removeFaceData(int index) {
    unsigned long lastPositionIndex = positionData.size() - POSITION_INSTANCE_SIZE;

    for (int i = index; i < index + POSITION_INSTANCE_SIZE; i++) {
        positionData[i] = positionData[lastPositionIndex + i - index];
    }

    positionData = std::vector<float>(positionData.begin(), positionData.end() - POSITION_INSTANCE_SIZE);

    int startIndex = (index / POSITION_INSTANCE_SIZE) * TEXTURE_INSTANCE_SIZE;

    unsigned long lastTextureIndex = textureIndices.size() - TEXTURE_INSTANCE_SIZE;
    unsigned long lastNormalIndex = normalIndices.size() - TEXTURE_INSTANCE_SIZE;
    unsigned long lastSpecularIndex = specularIndices.size() - TEXTURE_INSTANCE_SIZE;

    for (int i = startIndex; i < startIndex + TEXTURE_INSTANCE_SIZE; i++) {
        textureIndices[i] = textureIndices[lastTextureIndex + i - startIndex];
        normalIndices[i] = normalIndices[lastNormalIndex + i - startIndex];
        specularIndices[i] = specularIndices[lastSpecularIndex + i - startIndex];
    }

    textureIndices = std::vector<int>(textureIndices.begin(), textureIndices.end() - TEXTURE_INSTANCE_SIZE);
    normalIndices = std::vector<int>(normalIndices.begin(), normalIndices.end() - TEXTURE_INSTANCE_SIZE);
    specularIndices = std::vector<int>(specularIndices.begin(), specularIndices.end() - TEXTURE_INSTANCE_SIZE);

    vertexCount -= 6;
}

std::vector<int> Chunk::getIndices(Vec3 position, Face::FaceDirection direction) {
    std::vector<int> indices;

    for (int i = 0; i < positionData.size(); i += POSITION_INSTANCE_SIZE) {
        if (getIndicesHelper(position, direction, i)) {
            indices.emplace_back(i);
        }
    }

    return indices;
}

bool Chunk::getIndicesHelper(Vec3 position, Face::FaceDirection direction, int i) {
    std::vector<float> vertices = Face::getVertices(direction);

    for (int j = 0; j < vertices.size(); j += 3) {
        float x = vertices[j] + position.x;
        float y = vertices[j + 1] + position.y;
        float z = vertices[j + 2] + position.z;

        if (positionData[i + j] != x) {
            return false;
        }
        if (positionData[i + j + 1] != y) {
            return false;
        }
        if (positionData[i + j + 2] != z) {
            return false;
        }
    }
    return true;
}
