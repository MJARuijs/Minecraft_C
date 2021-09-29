#include "CheckBox.h"

#include <utility>

CheckBox::CheckBox(const std::string& id, ConstraintSet &constraints, bool checked, std::function<void(bool)> onChange,
                   Background *uncheckedBackground, Background * checkedBackground) : Button(id, constraints, uncheckedBackground), checked(checked), onChange(std::move(onChange)), uncheckedBackground(uncheckedBackground), checkedBackground(checkedBackground) {
    if (checked) {
        if (checkedBackground->getType() == COLORED) {
            this->setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(checkedBackground)));
        } else if (checkedBackground->getType() == TEXTURED) {
            this->setBackground(new TexturedBackground(dynamic_cast<TexturedBackground*>(checkedBackground)));
        }
    } else {
        if (uncheckedBackground->getType() == COLORED) {
            this->setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(uncheckedBackground)));
        } else if (uncheckedBackground->getType() == TEXTURED) {
            this->setBackground(new TexturedBackground(dynamic_cast<TexturedBackground*>(uncheckedBackground)));
        }
    }

    setOnClick([&]() {
        if (this->checked) {
            uncheck();
        } else {
            check();
        }
        this->onChange(this->checked);
    });
}

void CheckBox::check() {
    checked = true;
    if (checkedBackground->getType() == COLORED) {
        this->setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(checkedBackground)));
    } else if (checkedBackground->getType() == TEXTURED) {
        this->setBackground(new TexturedBackground(dynamic_cast<TexturedBackground*>(checkedBackground)));
    }
}

void CheckBox::uncheck() {
    checked = false;
    if (uncheckedBackground->getType() == COLORED) {
        this->setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(uncheckedBackground)));
    } else if (uncheckedBackground->getType() == TEXTURED) {
        this->setBackground(new TexturedBackground(dynamic_cast<TexturedBackground*>(uncheckedBackground)));
    }
}
