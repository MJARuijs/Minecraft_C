#pragma once

#include <functional>
#include "Item.h"
#include "backgrounds/Background.h"
#include "backgrounds/ColoredBackground.h"
#include "../animation/effects/Effect.h"
#include "../animation/Animator.h"
#include "../UniversalParameters.h"

class Button : public Item {

private:
    bool isClicked;
    bool isHovered;
    std::vector<Effect*> hoverEffects;
    std::vector<Effect*> clickEffects;
    std::function<void()> onClick;

    bool checkHovered(Mouse & mouse, float aspectRatio);
    bool isMouseOnButton(Mouse & mouse, float aspectRatio);

public:
    Button(const std::string& id, const ConstraintSet & constraints, Background * background = UniversalParameters::buttonBackground(), std::function<void()> onClick = [](){});

    bool update(Mouse & mouse, float aspectRatio, float deltaTime) override;

    Button & addHoverEffects(const std::vector<Effect*>& effects);
    Button & addClickEffects(const std::vector<Effect*>& effects);
    Button & setOnClick(std::function<void()> newOnClick);
    Button & setText(const std::string& text, Background * textBackground = UniversalParameters::textBackground(), const Color & color = UniversalParameters::textColor(), const Color &outlineColor = UniversalParameters::textOutlineColor(), Font * font = UniversalParameters::textFont());

};