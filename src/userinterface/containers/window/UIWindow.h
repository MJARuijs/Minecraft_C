#pragma once

#include <string>
#include <map>
#include "../../../graphics/Quad.h"
#include "../../../devices/input/Mouse.h"
#include "../../items/backgrounds/Background.h"
#include "../../items/backgrounds/ColoredBackground.h"
#include "TitleBar.h"
#include "../../items/Item.h"
#include "../../animation/Animator.h"

class UIWindow {

private:
    const std::string id;
    ConstraintSet constraints;
    Background * background;
    bool showing;

    std::vector<Item *> children;
    std::vector<std::string> boundlessChildren;
    std::map<Item*, std::vector<std::string>> postPonedItems;

    Quad quad;

    TitleBar * titleBar;
    Animator animator;

    void add(Item * item);
    void addItemWithDependencies(Item * item, std::vector<std::string> & requiredIds);

public:
    UIWindow(std::string id, ConstraintSet & windowConstraints, Background * background);
    UIWindow(std::string id, const Vec2 & scale, Background * background, float titleBarHeight, Background & titleBarBackground);

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] Vec2 getTranslation() const;
    [[nodiscard]] Vec2 getScale() const;

    void operator+=(Item & item);

    void setShouldShow(bool shouldShow);
    [[nodiscard]] bool shouldShow() const;

    Item & findById(const std::string & childId);
    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> getChildData();
    void allowChildToIgnoreBounds(const std::string & childId);
    bool isChildBoundless(const std::string & childId);

    void positionChild(Item & child);

    void draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram);
    bool update(Mouse & mouse, float aspectRatio, float deltaTime);

    void applyLayout(UILayout & layout, float duration);
};