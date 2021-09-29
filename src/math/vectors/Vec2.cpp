#include <stdexcept>
#include <iostream>
#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2::Vec2(float value) : x(value), y(value) {}

Vec2::Vec2() : x(0.0f), y(0.0f) {}

float Vec2::dot(const Vec2 & other) {
    return x * other.x + y * other.y;
}

float Vec2::length() {
    return sqrtf(x * x + y * y);
}

float & Vec2::operator[](int i) {
    if (i == 0) {
        return x;
    }
    if (i == 1) {
        return y;
    }
    throw std::runtime_error("Invalid index for 2D-vector");
}

Vec2 Vec2::operator+=(const Vec2 & other) {
    x += other.x;
    y += other.y;
    return *this;
}

std::string Vec2::toString() const {
    return "currentX=" + std::to_string(x) + " y=" + std::to_string(y);
}

Vec2 Vec2::fromString(const std::string & value) {
    unsigned long xStart = value.find('x');
    unsigned long xEquals = value.find('=', xStart);
    unsigned long xEnd = value.find(' ', xEquals);

    unsigned long yStart = value.find('y');
    unsigned long yEquals = value.find('=', yStart);
    unsigned long yEnd = value.find(' ', yEquals);
    if (yEnd == std::string::npos) {
        yEnd = value.size();
    }

    float x = std::stof(value.substr(xEquals + 1, xEnd - xEquals));
    float y = std::stof(value.substr(yEquals + 1, yEnd - yEquals));

    return Vec2(x, y);
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator*(float scale) const {
    return Vec2(x * scale, y * scale);
}
