#include "Item.h"
#include "backgrounds/TexturedBackground.h"

#include <utility>
#include <algorithm>

Item::Item(std::string id, const ConstraintSet & constraints, Background * background) : id(std::move(id)), constraints(constraints), background(background), goalTranslation(nullptr), goalScale(nullptr), baseBackground(
        nullptr) {
    if (background->getType() == COLORED) {
        baseBackground = new ColoredBackground(dynamic_cast<ColoredBackground*>(background));
    } else if (background->getType() == TEXTURED) {
        baseBackground = new TexturedBackground(dynamic_cast<TexturedBackground*>(background));
    }
}

std::string Item::getId() {
    return id;
}

Vec2 Item::getTranslation() const {
    return constraints.getTranslation();
}

Vec2 Item::getScale() const {
    return constraints.getScale();
}

Vec2 Item::getBasePosition() const {
    return basePosition;
}

void Item::setGoalTranslation(Vec2 * newGoalTranslation) {
    goalTranslation = newGoalTranslation;
}

void Item::setGoalScale(Vec2 * newGoalScale) {
    goalScale = newGoalScale;
}

Vec2 Item::getGoalTranslation() const {
    if (goalTranslation) {
        return Vec2(goalTranslation->x, goalTranslation->y);
    }
    return getTranslation();
}

Vec2 Item::getGoalScale() const {
    if (goalScale) {
        return Vec2(goalScale->x, goalScale->y);
    }
    return getScale();
}

void Item::place(const Vec2 & placement) {
    Vec2 difference = getTranslation() - placement;
    constraints.place(placement);

    for (auto & child : children) {
        child->place(child->getTranslation() - difference);
    }
}

void Item::translate(const Vec2 &translation) {
    constraints.translate(translation);

    for (auto & child : children) {
        child->translate(translation);
    }
}

void Item::setScale(const Vec2 &newScale) {
    constraints.setScale(newScale);
}

void Item::addToScale(const Vec2 &scaleAddition) {
    constraints.addToScale(scaleAddition);
}

std::pair<Vec2, Vec2> Item::getGoalDimensions() {
    Vec2 translation = goalTranslation != nullptr ? *goalTranslation : getTranslation();
    Vec2 scale = goalScale != nullptr ? *goalScale : getScale();
    return std::pair<Vec2, Vec2>(translation, scale);
}

std::vector<std::string> Item::getRequiredIds() {
    return constraints.determineRequiredIds();
}

void Item::operator+=(Item & item) {
    std::vector<std::string> requiredIds = item.getRequiredIds();
    if (requiredIds.empty()) {
        add(&item);
    } else {
        addItemWithDependencies(&item, requiredIds);
    }
}

std::vector<Item *> Item::getChildren() {
    return children;
}

void Item::allowChildToIgnoreBounds(const std::string & childId) {
    boundlessChildren.emplace_back(childId);
}

bool Item::isChildBoundless(const std::string & childId) {
    for (auto & child : children) {
        if (child->getId() == childId) {
            for (auto & boundlessChildId : boundlessChildren) {
                if (boundlessChildId == child->getId()) {
                    return true;
                }
            }
        }
    }
    return false;
}

Item & Item::findById(const std::string & childId) {
    for (auto & child : children) {
        if (child->getId() == childId) {
            return *child;
        }
    }
    throw std::runtime_error("No child was found with id: " + childId);
}

void Item::updateConstraint(const ConstraintType &type, const ConstraintDirection &direction, float newValue) {
    constraints.updateConstraint(type, direction, newValue);
}

void Item::position(const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblingData) {
    constraints.apply(parentTranslation, parentScale, siblingData);

    basePosition = getTranslation();
    baseScale = getScale();

    for (auto & child : children) {
        std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
        for (auto & child1 : children) {
            childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child1->getId(), std::pair<Vec2, Vec2>(child1->getTranslation(), child1->getScale())));
        }
        child->position(getTranslation(), getScale(), childData);
    }
}

void Item::draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram, bool allowedToOverdraw) {
    shaderProgram.set("translation", constraints.getTranslation());
    shaderProgram.set("scale", constraints.getScale());
    shaderProgram.set("allowedToOverdraw", allowedToOverdraw);

    background->setProperties(shaderProgram);
    quad.draw();

    for (auto & child : children) {
        child->draw(shaderProgram, textProgram, isChildBoundless(child->getId()));
    }
}

bool Item::update(Mouse & mouse, float aspectRatio, float deltaTime) {
    for (auto & child : children) {
        child->update(mouse, aspectRatio, deltaTime);
    }
    return false;
}

void Item::add(Item *item) {
    if (std::any_of(children.begin(), children.end(), [&](Item * child) {
        return child->getId() == item->getId();
    })) {
        std::cout << "Item with id already exists: " << item->getId() << std::endl;
        return;
    }

    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
    for (auto & child : children) {
        childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child->getId(), std::pair<Vec2, Vec2>(child->getTranslation(), child->getScale())));
    }

    item->position(getTranslation(), getScale(), childData);
    children.emplace_back(item);

    for (auto & postPonedItem : postPonedItems) {
        addItemWithDependencies(postPonedItem.first, postPonedItem.second);
    }
}

void Item::addItemWithDependencies(Item *item, std::vector<std::string> & requiredIds) {
    for (auto & child : children) {
        int i = 0;
        for (auto & requiredId : requiredIds) {
            if (requiredId == child->getId()) {
                requiredIds.erase(requiredIds.begin() + i);
            }
            i++;
        }
    }

    if (requiredIds.empty()) {
        postPonedItems.erase(item);
        add(item);
    } else {
        postPonedItems[item] = requiredIds;
    }
}

Background *Item::getBackground() {
    return background;
}

void Item::setBackground(Background *newBackground) {
    background = newBackground;
}

Background *Item::getBaseBackground() {
    return baseBackground;
}

std::vector<Animation *> Item::getAnimations() {
    return animations;
}

void Item::clearAnimations() {
    animations.clear();
}

void Item::addAnimations(const std::vector<Animation *>& newAnimations) {
    for (auto & animation : newAnimations) {
        animations.emplace_back(animation);
    }
}

void Item::addLayoutChange(const LayoutChange& layoutChange) {
    layoutChanges.emplace_back(layoutChange);
}

std::vector<LayoutChange> Item::getLayoutChanges() {
    return layoutChanges;
}

void Item::clearLayoutChanges() {
    layoutChanges.clear();
}
