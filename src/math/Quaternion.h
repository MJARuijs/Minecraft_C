#pragma once

#include <string>

class Quaternion {

private:
    float w;
    float x;
    float y;
    float z;

public:
    Quaternion(float w, float x, float y, float z);
    Quaternion();

    [[nodiscard]] float getW() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

    Quaternion operator+(Quaternion other) const;
    Quaternion operator*(float factor) const;
    Quaternion operator/(float factor) const;

    float dot(Quaternion & other) const;

    Quaternion normal();
    void normalize();
    float norm();
    float length();

    std::string toString() const;

    static Quaternion interpolate(Quaternion & a, Quaternion & b, float progress);
};