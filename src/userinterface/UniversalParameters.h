#pragma once

#include "items/backgrounds/ColoredBackground.h"
#include "items/backgrounds/TexturedBackground.h"
#include "text/font/Font.h"

class UniversalParameters {

public:
    static float aspectRatio;
    static int viewPortX;
    static int viewPortY;

    static float animationDuration;

    static Font * textFont();

    static Color primaryColor();
    static Color textColor();
    static Color textOutlineColor();

    static Color progressBarColor();
    static Color progressBarPausedColor();
    static Color progressBarCompletedColor();

    static ColoredBackground *progressBarBackground();

    static ColoredBackground *buttonBackground();

    static ColoredBackground *switchTrackOnBackground();
    static ColoredBackground *switchThumbOnBackground();
    static ColoredBackground *switchTrackOffBackground();
    static ColoredBackground *switchThumbOffBackground();

    static TexturedBackground *checkBoxCheckedBackground();
    static ColoredBackground *checkBoxUncheckedBackground();

    static ColoredBackground *textBackground();

};