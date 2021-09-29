#include "UIWindow.h"

#include <utility>
#include <algorithm>
#include "../../layout/constraints/constrainttypes/CenterConstraint.h"
#include "../../layout/constraints/constrainttypes/RelativeConstraint.h"
#include "../../UniversalParameters.h"

UIWindow::UIWindow(std::string id, ConstraintSet & windowConstraints, Background * background) : id(std::move(id)), constraints(windowConstraints), background(background), showing(false), titleBar(nullptr) {
    constraints.apply();
}

UIWindow::UIWindow(std::string id, const Vec2 &scale, Background * background, float titleBarHeight, Background &titleBarBackground) : id(std::move(id)), background(background), showing(false), titleBar(nullptr) {
    constraints += new CenterConstraint(HORIZONTAL);
    constraints += new CenterConstraint(VERTICAL);
    constraints += new RelativeConstraint(HORIZONTAL, scale.x);
    constraints += new RelativeConstraint(VERTICAL, scale.y);

    constraints.apply();

    this->titleBar = new TitleBar(titleBarHeight, &titleBarBackground, getTranslation(), getScale());
    if (titleBarHeight > 0.0f) {
        constraints.translate(Vec2(0.0f, -titleBar->getScale().y));
        constraints.addToScale(Vec2(0.0f, -titleBar->getScale().y));
    }
}

std::string UIWindow::getId() const {
    return id;
}

Vec2 UIWindow::getTranslation() const {
    return constraints.getTranslation();
}

Vec2 UIWindow::getScale() const {
    return constraints.getScale();
}

void UIWindow::operator+=(Item & item) {
    std::vector<std::string> requiredIds = item.getRequiredIds();
    if (requiredIds.empty()) {
        add(&item);
    } else {
        addItemWithDependencies(&item, requiredIds);
    }
}

void UIWindow::setShouldShow(bool shouldShow) {
    this->showing = shouldShow;
}

bool UIWindow::shouldShow() const {
    return showing;
}

Item & UIWindow::findById(const std::string & childId) {
    for (auto & child : children) {
        if (child->getId() == childId) {
            return *child;
        }
    }
    throw std::runtime_error("No child was found with id: " + childId);
}

std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> UIWindow::getChildData() {
    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
    for (auto & child : children) {
        childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child->getId(), std::pair<Vec2, Vec2>(child->getTranslation(), child->getScale())));
    }
    return childData;
}

void UIWindow::allowChildToIgnoreBounds(const std::string & childId) {
    boundlessChildren.emplace_back(childId);
}

bool UIWindow::isChildBoundless(const std::string & childId) {
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

void UIWindow::draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram) {
    shaderProgram.set("translation", constraints.getTranslation());
    shaderProgram.set("scale", constraints.getScale());
    shaderProgram.set("allowedToOverdraw", true);

    background->setProperties(shaderProgram);
    quad.draw();

    shaderProgram.set("parentTranslation", getTranslation());
    shaderProgram.set("parentScale", getScale());

    if (titleBar) {
        titleBar->draw(shaderProgram);
    }

    for (auto & child : children) {
        child->draw(shaderProgram, textProgram, isChildBoundless(child->getId()));
    }
}

bool UIWindow::update(Mouse &mouse, float aspectRatio, float deltaTime) {
    if (titleBar) {
        titleBar->update(mouse, aspectRatio, deltaTime);
    }

    for (auto & child : children) {
        if (!child->getAnimations().empty()) {
            animator += child->getAnimations();
            child->clearAnimations();
        }

        if (!child->getLayoutChanges().empty()) {
            for (auto & layoutChange : child->getLayoutChanges()) {
                if (child->getId() == layoutChange.id) {
                    animator.apply(layoutChange.constraints, child, UniversalParameters::animationDuration, getTranslation(), getScale(), layoutChange.extraAnimations);
                } else {
                    for (auto & item : child->getChildren()) {
                        if (item->getId() == layoutChange.id) {
                            animator.apply(layoutChange.constraints, item, UniversalParameters::animationDuration, child->getTranslation(), child->getScale(), layoutChange.extraAnimations);
                        }
                    }
                }
            }
            child->clearLayoutChanges();
        }
    }
    
    animator.update(deltaTime);
    for (auto & child : children) {
        child->update(mouse, aspectRatio, deltaTime);
    }

    return false;
}

void UIWindow::add(Item *item) {
    if (std::any_of(children.begin(), children.end(), [&](Item * child) {
        return child->getId() == item->getId();
    })) {
        std::cout << "Item with id already exists: " << item->getId() << std::endl;
        return;
    }
//    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
//    for (auto & child : children) {
//        childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child->getId(), std::pair<Vec2, Vec2>(child->getTranslation(), child->scaleVector())));
//    }
    item->position(getTranslation(), getScale(), getChildData());
    children.emplace_back(item);

    for (auto & postPonedItem : postPonedItems) {
        addItemWithDependencies(postPonedItem.first, postPonedItem.second);
    }
}

void UIWindow::addItemWithDependencies(Item *item, std::vector<std::string> & requiredIds) {
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

void UIWindow::applyLayout(UILayout & layout, float duration) {
    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
    for (auto & child : children) {
        childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child->getId(), std::pair<Vec2, Vec2>(child->getTranslation(), child->getScale())));
    }
    for (auto & child : children) {
        if (layout.containsConstraintForItem(child->getId())) {
            ConstraintSet childConstraint = layout.getConstraint(child->getId());
            animator.apply(childConstraint, child, duration, getTranslation(), getScale(), childData);
        }
    }
}
