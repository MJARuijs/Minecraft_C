#pragma once

#include "Background.h"

class ColoredBackground : public Background {

private:
    Color color;

public:
    explicit ColoredBackground(const Color & color, float cornerRadius = 0.0f, float outline = 0.0f, const Color & outlineColor = Color(0.0f, 0.0f, 0.0f, 0.0f));
    explicit ColoredBackground(ColoredBackground * background);

    Color getColor();
    void setColor(Color newColor);
    void setProperties(ShaderProgram & shaderProgram) override;

    BackgroundType getType() override;
};