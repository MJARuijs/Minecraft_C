#include "Switch.h"

#include <utility>
#include "Button.h"
#include "../layout/constraints/constrainttypes/PixelConstraint.h"
#include "../layout/constraints/constrainttypes/CenterConstraint.h"
#include "../layout/constraints/constrainttypes/RelativeConstraint.h"
#include "../layout/constraints/constrainttypes/AspectRatioConstraint.h"
#include "../animation/ColorAnimation.h"
#include "backgrounds/TexturedBackground.h"

Switch::Switch(const std::string & id, ConstraintSet &constraints, bool toggled, std::function<void(bool)> onChange,
               Background *trackOnBackground, Background *thumbOnBackground, Background *trackOffBackground,
               Background *thumbOffBackground) : Item(id, constraints, trackOffBackground),
                                                 trackOnBackground(trackOnBackground),
                                                 thumbOnBackground(thumbOnBackground),
                                                 trackOffBackground(trackOffBackground),
                                                 thumbOffBackground(thumbOffBackground),
                                                 thumb(nullptr),
                                                 toggled(toggled),
                                                 previousState(toggled),
                                                 onChange(std::move(onChange)),
                                                 switchOffConstraints(
                                                         new PixelConstraint(TO_LEFT, -0.1f),
                                                         new CenterConstraint(VERTICAL),
                                                         new RelativeConstraint(VERTICAL, 1.5f),
                                                         new AspectRatioConstraint(HORIZONTAL, 1.0f)
                                                 ),
                                                 switchOnConstraints(
                                                         new PixelConstraint(TO_RIGHT, -0.1f),
                                                         new CenterConstraint(VERTICAL),
                                                         new RelativeConstraint(VERTICAL, 1.5f),
                                                         new AspectRatioConstraint(HORIZONTAL, 1.0f)
                                                 ) {
    if (toggled) {
        if (trackOnBackground->getType() == COLORED) {
            setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(trackOnBackground)));
        }
        if (thumbOnBackground->getType() == COLORED) {
            thumb = new Button(id + "_thumb", switchOnConstraints, new ColoredBackground(dynamic_cast<ColoredBackground*>(thumbOnBackground)), [&]() {
                toggle();
            });
        } else if (thumbOnBackground->getType() == TEXTURED) {
            thumb = new Button(id + "_thumb", switchOnConstraints, new TexturedBackground(dynamic_cast<TexturedBackground*>(thumbOnBackground)), [&]() {
                toggle();
            });
        }
    } else {
        if (trackOnBackground->getType() == COLORED) {
            setBackground(new ColoredBackground(dynamic_cast<ColoredBackground*>(trackOffBackground)));
        }
        if (thumbOffBackground->getType() == COLORED) {
            thumb = new Button(id + "_thumb", switchOffConstraints, new ColoredBackground(dynamic_cast<ColoredBackground*>(thumbOffBackground)), [&]() {
                toggle();
            });
        }
    }

    add(thumb);
}

void Switch::turnOn(float duration) {
    toggled = true;
    std::vector<Animation*> extraAnimations;
    extraAnimations.emplace_back(new ColorAnimation(duration, thumb, new Color(dynamic_cast<ColoredBackground*>(thumbOnBackground)->getColor()), CHANGE_TO_COLOR, BACKGROUND_COLOR, true));
    extraAnimations.emplace_back(new ColorAnimation(duration, this, new Color(dynamic_cast<ColoredBackground*>(trackOnBackground)->getOutlineColor()), CHANGE_TO_COLOR, OUTLINE_COLOR, true));
    addLayoutChange(LayoutChange(thumb->getId(), switchOnConstraints, extraAnimations));
}

void Switch::turnOff(float duration) {
    toggled = false;
    std::vector<Animation*> extraAnimations;
    extraAnimations.emplace_back(new ColorAnimation(duration, thumb, new Color(dynamic_cast<ColoredBackground*>(thumbOffBackground)->getColor()), CHANGE_TO_COLOR, BACKGROUND_COLOR, true));
    extraAnimations.emplace_back(new ColorAnimation(duration, this, new Color(dynamic_cast<ColoredBackground*>(trackOffBackground)->getOutlineColor()), CHANGE_TO_COLOR, OUTLINE_COLOR, true));
    addLayoutChange(LayoutChange(thumb->getId(), switchOffConstraints, extraAnimations));
}

void Switch::toggle(float duration) {
    if (toggled) {
        turnOff(duration);
    } else {
        turnOn(duration);
    }
}

bool Switch::update(Mouse &mouse, float aspectRatio, float deltaTime) {
    if (previousState != toggled) {
        onChange(toggled);
    }
    previousState = toggled;
    return Item::update(mouse, aspectRatio, deltaTime);
}

void Switch::setOnChange(std::function<void(bool)> newOnChange) {
    onChange = std::move(newOnChange);
}
