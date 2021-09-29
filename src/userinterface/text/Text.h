#pragma once

#include <string>
#include "TextQuad.h"
#include "font/Font.h"
#include "../../math/Color.h"
#include "../../math/vectors/Vec2.h"
#include "../../graphics/samplers/Sampler.h"
#include "line/Line.h"
#include "../../graphics/shaders/ShaderProgram.h"

class Text {

private:
    std::string text;
    float fontSize;
    float maxLineWidth;
    Font * font;
    Color color;
    Color outlineColor;
    Vec2 translation;
    float scale;

    Sampler sampler;
    float spaceWidth;

    TextQuad * quad;

    std::vector<Line> createLines();
    [[nodiscard]] TextQuad * createTextMesh(const std::vector<Line> & lines, float aspectRatio) const;

public:
    Text(std::string text, float fontSize, float maxLineWidth, Font * font, const Color &color, const Color &outlineColor,
         float aspectRatio, const Vec2 &translation = Vec2(), float scale = 1.0f);

    void draw(ShaderProgram & shaderProgram, float aspectRatio);

    void setTranslation(const Vec2 & newTranslation);
    void translate(const Vec2 & translationAddition);


};