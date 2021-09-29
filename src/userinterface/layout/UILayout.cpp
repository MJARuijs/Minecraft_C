#include "UILayout.h"

UILayout::UILayout(std::string id, std::map<std::string, ConstraintSet> & itemChanges) : id(std::move(id)), itemChanges(itemChanges) {}

UILayout::UILayout(std::string id) : id(std::move(id)) {}

std::string UILayout::getId() {
    return id;
}

void UILayout::operator+=(const std::pair<std::string, ConstraintSet>& itemChange) {
    itemChanges[itemChange.first] = itemChange.second;
}

ConstraintSet UILayout::getConstraint(const std::string & itemId) {
    return itemChanges[itemId];
}

bool UILayout::containsConstraintForItem(const std::string &itemId) {
    for (auto & itemChange : itemChanges) {
        if (itemChange.first == itemId) {
            return true;
        }
    }
    return false;
}
