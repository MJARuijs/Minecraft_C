#pragma once

#include "Background.h"
#include "../../../graphics/textures/ImageMap.h"
#include "../../../graphics/samplers/Sampler.h"

class TexturedBackground : public Background {

private:
    ImageMap * textureMap;
    Sampler sampler;
    Color * backgroundColor;
    Color * overlayColor;

public:
    explicit TexturedBackground(ImageMap * textureMap, float cornerRadius = 0.0f, float outline = 0.0f, const Color& outlineColor = Color(0.0f, 0.0f, 0.0f, 0.0f), Color * overlayColor = nullptr, Color * backgroundColor = nullptr);
    explicit TexturedBackground(const std::string& path, float cornerRadius = 0.0f, float outline = 0.0f, const Color& outlineColor = Color(0.0f, 0.0f, 0.0f, 0.0f), Color * overlayColor = nullptr, Color * backgroundColor = nullptr);
    explicit TexturedBackground(TexturedBackground * background);

    void setProperties(ShaderProgram & shaderProgram) override;
    BackgroundType getType() override;

};
