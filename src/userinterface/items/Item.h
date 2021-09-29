#pragma once

#include <map>
#include <utility>
#include "../../graphics/shaders/ShaderProgram.h"

#include "../../devices/input/Mouse.h"
#include "backgrounds/Background.h"
#include "../../graphics/Quad.h"
#include "backgrounds/ColoredBackground.h"
#include "../animation/animationtypes/TransitionType.h"
#include "../layout/UILayout.h"
#include "../animation/Animation.h"

struct LayoutChange {
    std::string id;
    ConstraintSet constraints;
    std::vector<Animation *> extraAnimations;

    LayoutChange(std::string id, ConstraintSet & constraints, std::vector<Animation*> extraAnimations) : id(std::move(id)), constraints(constraints), extraAnimations(std::move(extraAnimations)) {}
};

class Item {

private:
    std::string id;

    Background * background;

    std::vector<std::string> boundlessChildren;
    std::map<Item*, std::vector<std::string>> postPonedItems;

    Vec2 basePosition;
    Vec2 baseScale;

    Background * baseBackground;

    Vec2* goalTranslation;
    Vec2* goalScale;

    void addItemWithDependencies(Item * item, std::vector<std::string> & requiredIds);

protected:
    ConstraintSet constraints;
    std::vector<Animation*> animations;
    std::vector<LayoutChange> layoutChanges;
    void add(Item * item);

    std::vector<Item *> children;

    Quad quad;

public:
    Item(std::string id, const ConstraintSet & constraints, Background * background);

    std::string getId();

    Background * getBackground();
    Background * getBaseBackground();
    void setBackground(Background * newBackground);

    [[nodiscard]] Vec2 getTranslation() const;
    [[nodiscard]] Vec2 getScale() const;

    void place(const Vec2 & placement);
    virtual void translate(const Vec2 & translation);

    void setScale(const Vec2 & newScale);
    void addToScale(const Vec2 & scaleAddition);

    std::vector<std::string> getRequiredIds();
    void operator+=(Item & item);

    [[nodiscard]] Vec2 getBasePosition() const;

    void setGoalTranslation(Vec2 * newGoalTranslation);
    void setGoalScale(Vec2 * newGoalScale);
    [[nodiscard]] Vec2 getGoalTranslation() const;
    [[nodiscard]] Vec2 getGoalScale() const;

    std::pair<Vec2, Vec2> getGoalDimensions();

    std::vector<Item*> getChildren();
    void allowChildToIgnoreBounds(const std::string & childId);
    bool isChildBoundless(const std::string & childId);
    Item & findById(const std::string & childId);

    void updateConstraint(const ConstraintType & type, const ConstraintDirection & direction, float newValue);

    virtual void position(const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblingData = std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>>());

    virtual void draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram, bool allowedToOverdraw);
    virtual bool update(Mouse & mouse, float aspectRatio, float deltaTime);

    void addAnimations(const std::vector<Animation*> & newAnimations);
    std::vector<Animation*> getAnimations();
    void clearAnimations();

    void addLayoutChange(const LayoutChange&);
    std::vector<LayoutChange> getLayoutChanges();
    void clearLayoutChanges();
};
