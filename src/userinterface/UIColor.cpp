#include "UIColor.h"

Color UIColor::white() {
    return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Color UIColor::greyLight() {
    return white() * 0.75f;
}

Color UIColor::grey() {
    return white() * 0.5f;
}

Color UIColor::greyDark() {
    return white() * 0.25f;
}

Color UIColor::black() {
    return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Color UIColor::redBright() {
    return Color(1.0f, 0.0f, 0.0f, 1.0f);
}

Color UIColor::redLight() {
    return redBright() * 0.75f;
}

Color UIColor::red() {
    return redBright() * 0.5f;
}

Color UIColor::redDark() {
    return redBright() * 0.25f;
}

Color UIColor::greenBright() {
    return Color(0.0f, 1.0f, 0.0f, 1.0f);
}

Color UIColor::greenLight() {
    return greenBright() * 0.75f;
}

Color UIColor::green() {
    return greenBright() * 0.5f;
}

Color UIColor::greenDark() {
    return greenBright() * 0.25f;
}

Color UIColor::blueBright() {
    return Color(0.0f, 0.0f, 1.0f, 1.0f);
}

Color UIColor::blueLight() {
    return blueBright() * 0.75f;
}

Color UIColor::blue() {
    return blueBright() * 0.5f;
}

Color UIColor::blueDark() {
    return blueBright() * 0.25f;
}

Color UIColor::yellowBright() {
    return Color(1.0f, 1.0f, 0.0f, 1.0f);
}

Color UIColor::yellowLight() {
    return yellowBright() * 0.75f;
}

Color UIColor::yellow() {
    return yellowBright() * 0.5f;
}

Color UIColor::yellowDark() {
    return yellowBright() * 0.25f;
}

Color UIColor::cyanBright() {
    return Color(0.0f, 1.0f, 1.0f, 1.0f);
}

Color UIColor::cyanLight() {
    return cyanBright() * 0.75f;
}

Color UIColor::cyan() {
    return cyanBright() * 0.5f;
}

Color UIColor::cyanDark() {
    return cyanBright() * 0.25f;
}

Color UIColor::purpleBright() {
    return Color(1.0f, 0.0f, 1.0f, 1.0f);
}

Color UIColor::purpleLight() {
    return purpleBright() * 0.75f;
}

Color UIColor::purple() {
    return purpleBright() * 0.5f;
}

Color UIColor::purpleDark() {
    return purpleBright() * 0.25f;
}

Color UIColor::transparent() {
    return Color(0.0f, 0.0f, 0.0f, 0.0f);
}


