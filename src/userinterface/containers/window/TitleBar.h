#pragma once

#include "../../../graphics/Quad.h"
#include "../../../devices/input/Mouse.h"
#include "../../items/backgrounds/ColoredBackground.h"
#include "../../../graphics/shaders/ShaderProgram.h"
#include "../../items/Item.h"

class TitleBar {

private:
    ConstraintSet constraints;
    Background * background;
    Quad quad;

public:
    TitleBar(float height, Background * background, const Vec2 & parentTranslation, const Vec2 & parentScale);

    [[nodiscard]] Vec2 getScale() const;

    void draw(ShaderProgram & shaderProgram);
    void update(Mouse & mouse, float aspectRatio, float deltaTime);

};