#pragma once
#include <cmath>
#include <string>

class Vec2 {

public:
    Vec2(float x, float y);
    Vec2(float value);
    Vec2();

    float x;
    float y;

    float dot(const Vec2 & other);
    float length();
    float normalize();

    float & operator[] (int i);
    Vec2 operator* (float scale) const;
    Vec2 operator+ (const Vec2 & other) const;
    Vec2 operator- (const Vec2 & other) const;
    Vec2 operator+= (const Vec2 & other);

    std::string toString() const;
    static Vec2 fromString(const std::string & value);
};
