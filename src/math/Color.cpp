#include <stdexcept>
#include <sstream>
#include "Color.h"

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}

Color::Color(int r, int g, int b, int a) : r((float)r / 255.0f), g((float)g / 255.0f), b((float)b / 255.0f), a((float)a / 255.0f) {}

Color::Color(int r, int g, int b) : r((float)r / 255.0f), g((float)g / 255.0f), b((float)b / 255.0f), a(1.0f) {}

Color::Color(const Color & otherColor) : r(otherColor.r), g(otherColor.g), b(otherColor.b), a(otherColor.a) {}

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

float &Color::operator[](int i) {
    return get(i);
}

float &Color::get(int i) {
    if (i == 0) {
        return r;
    }
    if (i == 1) {
        return g;
    }
    if (i == 2) {
        return b;
    }
    if (i == 3) {
        return a;
    }

    throw std::runtime_error(&"Index out of bounds for color: " [i]);
}

Color & Color::set(int i, float value) {
    if (i == 0) {
        r = value;
    } else if (i == 1) {
        g = value;
    } else if (i == 2) {
        b = value;
    } else if (i == 3) {
        a = value;
    } else {
        throw std::runtime_error(&"Index out of bounds for color: " [i]);
    }

    return *this;
}

Color Color::operator+(Color &other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Vec3 Color::rgb() const {
    return Vec3(r, g, b);
}

void Color::setR(float newR) {
    r = newR;
}

void Color::setG(float newG) {
    g = newG;
}

void Color::setB(float newB) {
    b = newB;
}

void Color::setA(float newA) {
    a = newA;
}

float Color::getR() const {
    return r;
}

float Color::getG() const {
    return g;
}

float Color::getB() const {
    return b;
}

float Color::getA() const {
    return a;
}

bool Color::operator==(Color & other) const {
    if (std::abs(r - other.r) > 0.0005f) {
        return false;
    }
    if (std::abs(g - other.g) > 0.0005f) {
        return false;
    }
    if (std::abs(b - other.b) > 0.0005f) {
        return false;
    }
    if (std::abs(a - other.a) > 0.0005f) {
        return false;
    }
    return true;
}

Color Color::copy() const {
    return Color(r, g, b, a);
}

Color Color::operator-() const {
    return Color(-r, -g, -b, -a);
}

std::string Color::toString() {
    std::ostringstream stringStream;
    stringStream << "r=" << r << ", g=" << g << ", b=" << b << ", a=" << a;
    return stringStream.str();
}

Color Color::operator*(float scale) const {
    return Color(r * scale, g * scale, b * scale, a);
}
