#include <cmath>
#include <stdexcept>
#include <cmath>
#include "Vec3.h"
#include "../../util/FloatUtils.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(int x, int y, int z) : x((float)x), y((float)y), z((float)z) {}

Vec3::Vec3() :x(0.0f), y(0.0f), z(0.0f) {}

float & Vec3::operator[](int i) {
    if (i == 0) {
        return x;
    }
    if (i == 1) {
        return y;
    }
    if (i == 2) {
        return z;
    }
    throw std::runtime_error("Invalid index for 3D-vector");
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator*(float scale) const {
    return Vec3(x * scale, y * scale, z * scale);
}

Vec3 Vec3::operator/(float scale) const {
    return Vec3(x / scale, y / scale, z / scale);
}

//Vec3 Vec3::operator+(Vec3 &vector) const {
//    return Vec3(x + vector.x, y + vector.y, z + vector.z);
//}

Vec3 Vec3::operator+(Vec3 vector) const {
    return Vec3(x + vector.x, y + vector.y, z + vector.z);
}

//Vec3 Vec3::operator-(Vec3 &vector) const {
//    return Vec3(x - vector.x, y - vector.y, z - vector.z);
//}

Vec3 Vec3::operator-(Vec3 vector) const {
    return Vec3(x - vector.x, y - vector.y, z - vector.z);
}

float Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::unit() const {
    float length = this->length();
    return Vec3(x / length, y / length, z / length);
}

float Vec3::dot(Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

bool Vec3::operator==(Vec3 other) const {
        if (!FloatUtils::compare(x, other.x)) {
            return false;
        }
    if (!FloatUtils::compare(y, other.y)) {
        return false;
    }
    if (!FloatUtils::compare(z, other.z)) {
        return false;
    }
    return true;
}

std::string Vec3::toString() const {
    return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ">";
}
