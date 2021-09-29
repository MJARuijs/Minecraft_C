#pragma once
#include <string>
#include <vector>
#include "Vec3.h"

class Vec4 {

public:
    float x;
    float y;
    float z;
    float w;

    Vec4(float x, float y, float z, float w);
    explicit Vec4(const Vec3 & vector);
    Vec4();

    float & operator[] (int i);

    [[nodiscard]] Vec3 xyz() const;

    static Vec4 fromString(const std::string & line);
};