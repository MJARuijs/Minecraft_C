#include "UniversalParameters.h"
#include "UIColor.h"
#include "text/font/FontCache.h"

float UniversalParameters::aspectRatio = 1.0f;
int UniversalParameters::viewPortX = 1;
int UniversalParameters::viewPortY = 1;

float UniversalParameters::animationDuration = 0.1f;

Font * UniversalParameters::textFont() {
    return FontCache::get("res/fonts/arial_df.png", aspectRatio);
}

Color UniversalParameters::primaryColor() {
    return UIColor::blueBright();
}

Color UniversalParameters::textColor() {
    return UIColor::white();
}

Color UniversalParameters::textOutlineColor() {
    return UIColor::black();
}

Color UniversalParameters::progressBarColor() {
    return primaryColor();
}

Color UniversalParameters::progressBarPausedColor() {
    return UIColor::yellowLight();
}

Color UniversalParameters::progressBarCompletedColor() {
    return UIColor::greenLight();
}

ColoredBackground *UniversalParameters::progressBarBackground() {
    return new ColoredBackground(UIColor::grey());
}

ColoredBackground *UniversalParameters::buttonBackground() {
    return new ColoredBackground(primaryColor(), 10.0f, 0.09f, UIColor::white());
}

ColoredBackground *UniversalParameters::switchTrackOnBackground() {
    return new ColoredBackground(UIColor::transparent(), 90.0f, 0.09f, Color(33, 73, 107, 255));
}

ColoredBackground *UniversalParameters::switchThumbOnBackground() {
    return new ColoredBackground(Color(65, 162, 239, 255), 90.0f);
}

ColoredBackground *UniversalParameters::switchTrackOffBackground() {
    return new ColoredBackground(UIColor::transparent(), 90.0f, 0.09f, Color(74, 74, 74, 255));
}

ColoredBackground *UniversalParameters::switchThumbOffBackground()  {
    return new ColoredBackground(Color(185, 185, 185, 255), 90.0f);
}

TexturedBackground *UniversalParameters::checkBoxCheckedBackground() {
    return new TexturedBackground("res/textures/userinterface/check_mark.png", 15.0f, 0.1f, UIColor::white(), new Color(UIColor::white()), new Color(primaryColor()));
}

ColoredBackground *UniversalParameters::checkBoxUncheckedBackground() {
    return new ColoredBackground(UIColor::transparent(), 15.0f, 0.1f, UIColor::white());
}

ColoredBackground *UniversalParameters::textBackground() {
    return new ColoredBackground(UIColor::transparent());
}
