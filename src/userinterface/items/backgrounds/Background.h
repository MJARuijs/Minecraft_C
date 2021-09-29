#pragma once

#include "../../../graphics/shaders/ShaderProgram.h"
#include "../../../math/Color.h"
#include "BackgroundType.h"

class Background {

protected:
    float cornerRadius;
    float outline;
    Color outlineColor;

public:
    Background(float cornerRadius, float outline, const Color & outlineColor);

    [[nodiscard]] float getCornerRadius() const;
    Color getOutlineColor();
    void setOutlineColor(Color & newOutlineColor);

    virtual void setProperties(ShaderProgram & shaderProgram);

    virtual BackgroundType getType() = 0;
};