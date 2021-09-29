#include "Background.h"

Background::Background(float cornerRadius, float outline, const Color &outlineColor) : cornerRadius(cornerRadius), outline(outline), outlineColor(outlineColor) {
    if (cornerRadius < 0.0f) {
        this->cornerRadius = 0.0f;
    }
    if (cornerRadius > 90.0f) {
        this->cornerRadius = 90.0f;
    }
}

float Background::getCornerRadius() const {
    return cornerRadius;
}

Color Background::getOutlineColor() {
    return outlineColor;
}

void Background::setProperties(ShaderProgram & shaderProgram) {
    shaderProgram.set("cornerRadius", cornerRadius);
    shaderProgram.set("outline", outline);
    shaderProgram.set("outlineColor", outlineColor);
}

void Background::setOutlineColor(Color &newOutlineColor) {
    outlineColor = newOutlineColor;
}
