#include <vector>
#include "Character.h"
#include "../../../util/StringUtils.h"

Character::Character(char id, float x, float y, float width, float height, float xOffset, float yOffset,
                     float quadWidth, float quadHeight, float advance) : id(id), x(x), y(y), width(width),
                                                                         height(height), xOffset(xOffset),
                                                                         yOffset(yOffset), quadWidth(quadWidth),
                                                                         quadHeight(quadHeight), advance(advance),
                                                                         xMaxTexCoord(x + width),
                                                                         yMaxTexCoord(y + height) {}

float Character::LINE_HEIGHT = 0.03f;

float Character::DESIRED_PADDING = 8.0f;

char Character::getId() const {
    return id;
}

float Character::getX() const {
    return x;
}

float Character::getY() const {
    return y;
}

float Character::getWidth() const {
    return width;
}

float Character::getHeight() const {
    return height;
}

float Character::getXOffset() const {
    return xOffset;
}

float Character::getYOffset() const {
    return yOffset;
}

float Character::getQuadWidth() const {
    return quadWidth;
}

float Character::getQuadHeight() const {
    return quadHeight;
}

float Character::getAdvance() const {
    return advance;
}

float Character::getXMaxTexCoord() const {
    return xMaxTexCoord;
}

float Character::getYMaxTexCoord() const {
    return yMaxTexCoord;
}

Character Character::fromLine(const std::string &line, MetaData &metaData, float aspectRatio) {
    auto textureSize = (float)metaData.getScaleW();
    float lineHeightPixels = (float) metaData.getLineHeight() - metaData.getPaddingHeight();

    float verticalSize = LINE_HEIGHT / lineHeightPixels;
    float horizontalSize = verticalSize / aspectRatio;

    std::vector<std::string> values = StringUtils::split(line, ' ');
//std::vector<std::string> values = {
//
//};

    int id = stoi(values[0]);
    float x = (std::stof(values[1]) + (metaData.getPaddingLeft() - DESIRED_PADDING)) / textureSize;
    float y = (std::stof(values[2]) + (metaData.getPaddingTop() - DESIRED_PADDING)) / textureSize;

    float width = std::stof(values[3]) - (metaData.getPaddingWidth() - 2.0f * DESIRED_PADDING);
    float height = std::stof(values[4]) - (metaData.getPaddingHeight() - 2.0f * DESIRED_PADDING);

    float quadWidth = width * horizontalSize;
    float quadHeight = height * verticalSize;

    float xTextureSize = width / textureSize;
    float yTextureSize = height / textureSize;

    float xOffset = (std::stof(values[5]) + metaData.getPaddingLeft() - DESIRED_PADDING) * horizontalSize;
    float yOffset = (std::stof(values[6]) + metaData.getPaddingTop() - DESIRED_PADDING) * verticalSize;
    float advance = (std::stof(values[7]) - metaData.getPaddingWidth()) * horizontalSize;

    return Character((char)id, x, y, xTextureSize, yTextureSize, xOffset, yOffset, quadWidth, quadHeight, advance);
}
