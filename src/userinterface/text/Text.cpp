#include "Text.h"

#include <utility>

Text::Text(std::string text, float fontSize, float maxLineWidth, Font * font, const Color &color, const Color &outlineColor, float aspectRatio,
           const Vec2 &translation, float scale) : text(std::move(text)), fontSize(fontSize),
                                                   maxLineWidth(maxLineWidth), font(font),
                                                   color(color), outlineColor(outlineColor), translation(translation), scale(scale),
                                                   sampler(0, NEAREST, LINEAR, EDGE, true),
                                                   spaceWidth(0.0f), quad(nullptr) {
    spaceWidth = font->getSpaceWidth() * fontSize;
    quad = createTextMesh(createLines(), aspectRatio);
}

void Text::draw(ShaderProgram &shaderProgram, float aspectRatio) {
    shaderProgram.start();
    shaderProgram.set("textureAtlas", sampler.index);
    shaderProgram.set("translation", translation);
    shaderProgram.set("aspectRatio", aspectRatio);
    shaderProgram.set("scale", scale);
    shaderProgram.set("color", color);
    shaderProgram.set("outlineColor", outlineColor);

    sampler.bind(font->getTextureAtlas());
    quad->draw();

    ShaderProgram::stop();
}

std::vector<Line> Text::createLines() {
    std::vector<Line> lines;

    Line currentLine(maxLineWidth);
    Word currentWord(fontSize);

    for (auto & character : text) {
        if (character == ' ') {
            if (currentLine.addWord(currentWord, spaceWidth)) {
                currentWord = Word(fontSize);
            } else {
                lines.emplace_back(Line(maxLineWidth, currentWord));
                currentWord = Word(fontSize);
            }
        } else {
            currentWord += font->getCharacter(character);
        }
    }

    if (currentLine.addWord(currentWord, spaceWidth)) {
        lines.emplace_back(currentLine);
    } else {
        lines.emplace_back(currentLine);
        lines.emplace_back(Line(maxLineWidth, currentWord));
    }

    return lines;
}

TextQuad *Text::createTextMesh(const std::vector<Line> &lines, float aspectRatio) const {
    float xCursor = 0.0f;
    float yCursor = 0.0f;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> texCoords;

    for (auto & line : lines) {
        for (auto & word : line.getWords()) {
            for (auto & character : word.getCharacters()) {
                float x = (xCursor + character.getXOffset() * fontSize) / aspectRatio;
                float y = (yCursor + character.getYOffset() * fontSize);

                float letterMaxX = x + (character.getQuadWidth() * fontSize) / aspectRatio;
                float letterMaxY = y + (character.getQuadHeight() * fontSize);

                vertices.emplace_back(x);
                vertices.emplace_back(-y);

                vertices.emplace_back(x);
                vertices.emplace_back(-letterMaxY);

                vertices.emplace_back(letterMaxX);
                vertices.emplace_back(-letterMaxY);

                vertices.emplace_back(letterMaxX);
                vertices.emplace_back(-letterMaxY);

                vertices.emplace_back(letterMaxX);
                vertices.emplace_back(-y);

                vertices.emplace_back(x);
                vertices.emplace_back(-y);

                texCoords.emplace_back(character.getX());
                texCoords.emplace_back(character.getY());

                texCoords.emplace_back(character.getX());
                texCoords.emplace_back(character.getYMaxTexCoord());

                texCoords.emplace_back(character.getXMaxTexCoord());
                texCoords.emplace_back(character.getYMaxTexCoord());

                texCoords.emplace_back(character.getXMaxTexCoord());
                texCoords.emplace_back(character.getYMaxTexCoord());

                texCoords.emplace_back(character.getXMaxTexCoord());
                texCoords.emplace_back(character.getY());

                texCoords.emplace_back(character.getX());
                texCoords.emplace_back(character.getY());

                xCursor += character.getAdvance() * fontSize;
            }
            xCursor += spaceWidth;
        }
        xCursor = 0.0f;
        yCursor += Character::LINE_HEIGHT * fontSize;
    }

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::min();

    for (int i = 0; i < vertices.size(); i += 2) {
        float x = vertices[i];
        float y = vertices[i + 1];

        if (x < minX) {
            minX = x;
        }
        if (x > maxX) {
            maxX = x;
        }
        if (y < minY) {
            minY = y;
        }
        if (y > maxY) {
            maxY = y;
        }
    }

    float xDifference = maxX - minX;
    float yDifference = minY - maxY;

    std::vector<float> repositionedVertices;

    for (int i = 0; i < vertices.size(); i += 2) {
        float x = vertices[i];
        float y = vertices[i + 1];

        repositionedVertices.emplace_back(x - xDifference / 2.0f);
        repositionedVertices.emplace_back(y - yDifference / 2.0f);
    }

    return new TextQuad(repositionedVertices, texCoords);
}

void Text::setTranslation(const Vec2 & newTranslation) {
    translation = newTranslation;
}

void Text::translate(const Vec2 & translationAddition) {
    translation += translationAddition;
}
