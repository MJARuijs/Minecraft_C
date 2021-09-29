#pragma once

#include <string>

class Vec3 {

public:
    float x;
    float y;
    float z;

    Vec3(float x, float y, float z);
    Vec3(int x, int y, int z);
    Vec3();
    ~Vec3() = default;

    float & operator[] (int i);
    Vec3 operator- () const;
    Vec3 operator* (float scale) const;
    Vec3 operator/ (float scale) const;
//    Vec3 operator+ (Vec3 & vector) const;
    Vec3 operator+ (Vec3 vector) const;
//    Vec3 operator- (Vec3 & vector) const;
    Vec3 operator- (Vec3 vector) const;
    Vec3 & operator+=(const Vec3 & other);

    bool operator==(Vec3 other) const;

    float dot(Vec3 & other) const;

    [[nodiscard]] float length() const;
    [[nodiscard]] Vec3 unit() const;

    [[nodiscard]] std::string toString() const;

};
