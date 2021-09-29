#include "TextBox.h"

#include <utility>

TextBox::TextBox(const std::string &id, const ConstraintSet &constraints, std::string textString, float aspectRatio,
                 float size, Background *background,
                 const Color &color, const Color &outlineColor, Font * font) : Item(id, constraints, background),
                                                              textString(std::move(textString)),
                                                              aspectRatio(aspectRatio),
                                                              size(size), background(background), color(color), outlineColor(outlineColor),
                                                              font(font), text(nullptr) {}

void TextBox::draw(ShaderProgram &shaderProgram, ShaderProgram &textProgram, bool allowedToOverdraw) {
    Item::draw(shaderProgram, textProgram, allowedToOverdraw);
    text->draw(textProgram, aspectRatio);
    shaderProgram.start();
}

void TextBox::position(const Vec2 &parentTranslation, const Vec2 &parentScale,
                       const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> &siblingData) {

    Item::position(parentTranslation, parentScale, siblingData);
    float maxLength = getScale().x;
    text = new Text(textString, 1.0f, maxLength, font, color, outlineColor, aspectRatio, Vec2(), size);
    text->setTranslation(getTranslation());
}

void TextBox::translate(const Vec2 &newTranslation) {
    Item::translate(newTranslation);
    text->translate(newTranslation);
}
