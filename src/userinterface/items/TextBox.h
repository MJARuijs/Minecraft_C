#pragma once

#include <string>
#include "backgrounds/Background.h"
#include "../text/font/Font.h"
#include "../text/Text.h"
#include "Item.h"
#include "../UniversalParameters.h"

class TextBox : public Item {

private:
    std::string textString;
    float aspectRatio;
    float size;
    Background * background;
    Color color;
    Color outlineColor;
    Font * font;

    Text * text;

public:
    TextBox(const std::string & id, const ConstraintSet & constraints, std::string textString, float aspectRatio, float size, Background *background = UniversalParameters::textBackground(), const Color &color = UniversalParameters::textColor(), const Color &outlineColor = UniversalParameters::textOutlineColor(),
            Font * font = UniversalParameters::textFont());

    void draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram, bool allowedToOverdraw) override;

    void translate(const Vec2 & newTranslation) override;
    void position(const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblingData) override;
};