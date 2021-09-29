#pragma once

#include <string>
#include "../MetaData.h"

class Character {

private:
    char id;
    float x;
    float y;
    float width;
    float height;
    float xOffset;
    float yOffset;
    float quadWidth;
    float quadHeight;
    float advance;
    float xMaxTexCoord;
    float yMaxTexCoord;

public:
    Character(char id, float x, float y, float width, float height, float xOffset, float yOffset, float quadWidth, float quadHeight, float advance);

    [[nodiscard]] char getId() const;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getWidth() const;

    [[nodiscard]] float getHeight() const;

    [[nodiscard]] float getXOffset() const;

    [[nodiscard]] float getYOffset() const;

    [[nodiscard]] float getQuadWidth() const;

    [[nodiscard]] float getQuadHeight() const;

    [[nodiscard]] float getAdvance() const;

    [[nodiscard]] float getXMaxTexCoord() const;

    [[nodiscard]] float getYMaxTexCoord() const;

    static float LINE_HEIGHT;
    static float DESIRED_PADDING;

    static Character fromLine(const std::string & line, MetaData & metaData, float aspectRatio);
};