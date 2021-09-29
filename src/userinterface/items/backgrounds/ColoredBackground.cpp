#include "ColoredBackground.h"

ColoredBackground::ColoredBackground(const Color &color, float cornerRadius, float outline, const Color & outlineColor) : Background(cornerRadius, outline, outlineColor), color(color) {}

ColoredBackground::ColoredBackground(ColoredBackground *background) : Background(background->cornerRadius, background->outline, background->outlineColor), color(background->getColor()) {}

Color ColoredBackground::getColor() {
    return color;
}

void ColoredBackground::setColor(Color newColor) {
    color = newColor;
}

void ColoredBackground::setProperties(ShaderProgram & shaderProgram) {
    Background::setProperties(shaderProgram);
    shaderProgram.set("color", color);
    shaderProgram.set("textured", false);
}

BackgroundType ColoredBackground::getType() {
    return COLORED;
}

