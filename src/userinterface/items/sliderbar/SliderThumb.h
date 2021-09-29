#pragma once

#include "../Item.h"

class SliderThumb : public Item {

private:
    float parentMinX;
    float parentMaxX;
    bool moving;

    bool isMouseOnButton(Mouse & mouse, float aspectRatio);

public:
    SliderThumb(std::string id, const ConstraintSet & constraints, Background * background);

    bool update(Mouse & mouse, float aspectRatio, float deltaTime) override;
    void position(const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblingData) override;

};