#pragma once

#include "Item.h"
#include "../UniversalParameters.h"
#include "Button.h"

class CheckBox : public Button {

private:
    bool checked;
    std::function<void(bool)> onChange;
    Background * uncheckedBackground;
    Background * checkedBackground;

public:
    CheckBox(const std::string& id, ConstraintSet & constraints, bool checked, std::function<void(bool)>  onChange = [](bool){}, Background * uncheckedBackground = UniversalParameters::checkBoxUncheckedBackground(), Background * checkedBackground = UniversalParameters::checkBoxCheckedBackground());

    void check();
    void uncheck();
};