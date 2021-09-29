#include "Quaternion.h"

#include <cmath>

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

float Quaternion::getW() const {
    return w;
}

float Quaternion::getX() const {
    return x;
}

float Quaternion::getY() const {
    return y;
}

float Quaternion::getZ() const {
    return z;
}

Quaternion Quaternion::operator*(float factor) const {
    return Quaternion(w * factor, x * factor, y * factor, z * factor);
}

Quaternion Quaternion::operator+(Quaternion other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
}

Quaternion Quaternion::operator/(float factor) const {
    return Quaternion(w / factor, x / factor, y / factor, z / factor);
}

float Quaternion::dot(Quaternion & other) const {
    return (w * other.w) + (x * other.x) + (y * other.y) + (z * other.z);
}

Quaternion Quaternion::normal() {
    return Quaternion(w, x, y, z) / norm();
}

float Quaternion::norm() {
    return std::sqrt(dot(*this));
}

void Quaternion::normalize() {
    float length = norm();
    w /= length;
    x /= length;
    y /= length;
    z /= length;
}

float Quaternion::length() {
    return norm();
}

//Mat4 Quaternion::toMatrix() {
//    Quaternion norm = normal();
//
//    float x = norm.x;
//    float y = norm.y;
//    float z = norm.z;
//    float w = norm.w;
//
//    std::vector<float> elements = {
//            1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
//            2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
//            2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x* w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
//            0.0f, 0.0f, 0.0f, 1.0f
//    };
//
//    return Mat4(elements);
//}

Quaternion Quaternion::interpolate(Quaternion &a, Quaternion &b, float progress) {
    float dot = a.dot(b);
    float remaining = 1.0f - progress;
    if (dot < 0) {
        return (a * remaining + b * -progress).normal();
    } else {
        return (a * remaining + b * progress).normal();
    }
}

std::string Quaternion::toString() const {
    return "<" + std::to_string(w) + ", " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ">";
}
//
//Quaternion Quaternion::fromMatrix(Mat4 &matrix) {
//    float m00 = matrix(0, 0);
//    float m11 = matrix(1, 1);
//    float m22 = matrix(2, 2);
//    float trace = m00 + m11 + m22;
//
//    if (trace > 0) {
//        float s = std::sqrt(trace + 1.0f) * 2;
//        float w = 0.25f * s;
//        float x = (matrix(2, 1) - matrix(1, 2)) / s;
//        float y = (matrix(0, 2) - matrix(2, 0)) / s;
//        float z = (matrix(1, 0) - matrix(0, 1)) / s;
//        return Quaternion(w, x, y, z);
//    }
//    if (m00 > m11 && m00 > m22) {
//        float s = std::sqrt(1.0f + m00 - m11 - m22) * 2;
//        float w = (matrix(2, 1) - matrix(1, 2)) / s;
//        float x = 0.25f * s;
//        float y = (matrix(0, 1) + matrix(1, 0)) / s;
//        float z = (matrix(0, 2) + matrix(2, 0)) / s;
//        return Quaternion(w, x, y, z);
//    }
//    if (m11 > m22) {
//        float s = std::sqrt(1.0f + m11 - m00 - m22) * 2;
//        float w = (matrix(0, 2) - matrix(2, 0)) / s;
//        float x = (matrix(0, 1) + matrix(1, 0)) / s;
//        float y = 0.25f * s;
//        float z = (matrix(1, 2) + matrix(2, 1)) / s;
//        return Quaternion(w, x, y, z);
//    }
//    float s = std::sqrt(1.0f + m22 - m00 - m11) * 2;
//    float w = (matrix(1, 0) - matrix(0, 1)) / s;
//    float x = (matrix(0, 2) + matrix(2, 0)) / s;
//    float y = (matrix(1, 2) + matrix(2, 1)) / s;
//    float z = 0.25f * s;
//    return Quaternion(w, x, y, z);
//}
