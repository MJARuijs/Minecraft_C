#include <stdexcept>
#include "Vec4.h"
#include "../../util/StringUtils.h"

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vec4::Vec4(const Vec3 &vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f) {}

float & Vec4::operator[](int i) {
    if (i == 0) {
        return x;
    }
    if (i == 1) {
        return y;
    }
    if (i == 2) {
        return z;
    }
    if (i == 3) {
        return w;
    }
    throw std::runtime_error("Invalid index for 3D-vector");
}

Vec4 Vec4::fromString(const std::string& line) {
    std::vector<std::string> values = StringUtils::split(line, ',');
    return Vec4(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]), std::stof(values[3]));
}

Vec3 Vec4::xyz() const {
    return Vec3(x, y, z);
}
