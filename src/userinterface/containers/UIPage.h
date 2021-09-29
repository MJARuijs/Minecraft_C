#pragma once

#include <map>
#include "../../graphics/Quad.h"

#include "../items/Item.h"

class UIPage {

private:
    std::map<Item, std::vector<std::string>> postPonedItems;
    std::vector<std::string> boundlessChildren;

    bool shouldShow;

protected:
    const std::string id;
    Quad quad;
    std::vector<Item> children;

public:
    UIPage(const std::string & id);

    Vec2 getTranslation();
    Vec2 getScale();

    Item & findById(const std::string & id);
    void allowChildToIgnoreBounds(const std::string & id);
    bool isChildBoundless(const std::string & id);

    bool update(Mouse & mouse, float aspectRatio, float deltaTime);

    void apply();
};