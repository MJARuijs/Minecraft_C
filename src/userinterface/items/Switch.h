#pragma once

#include <functional>
#include "backgrounds/Background.h"
#include "../UniversalParameters.h"
#include "Item.h"
#include "Button.h"

class Switch : public Item {

private:
    bool toggled;
    bool previousState;

    Background *trackOnBackground;
    Background *thumbOnBackground;
    Background *trackOffBackground;
    Background *thumbOffBackground;

    std::function<void(bool)> onChange;

    Button *thumb;

    ConstraintSet switchOffConstraints;
    ConstraintSet switchOnConstraints;

public:
    Switch(const std::string & id, ConstraintSet &constraints, bool toggled, std::function<void(bool)> onChange = [](bool){},
           Background *trackOnBackground = UniversalParameters::switchTrackOnBackground(),
           Background *thumbOnBackground = UniversalParameters::switchThumbOnBackground(),
           Background *trackOffBackground = UniversalParameters::switchTrackOffBackground(),
           Background *thumbOffBackground = UniversalParameters::switchThumbOffBackground());

    void turnOn(float duration = UniversalParameters::animationDuration);
    void turnOff(float duration = UniversalParameters::animationDuration);
    void toggle(float duration = UniversalParameters::animationDuration);

    void setOnChange(std::function<void(bool)> newOnChange);

    bool update(Mouse & mouse, float aspectRatio, float deltaTime) override;

};