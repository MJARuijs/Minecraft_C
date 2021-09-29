#include "Mat4.h"
#include "../Quaternion.h"

#include <utility>

Mat4::Mat4() : elements {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
} {}

Mat4::Mat4(float scale) : Mat4(std::vector<float> {
        scale, 0.0f, 0.0f, 0.0f,
        0.0f, scale, 0.0f, 0.0f,
        0.0f, 0.0f, scale, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
}) {}

Mat4::Mat4(std::vector<float> elements) : elements(std::move(elements)) {}

float & Mat4::operator()(int row, int col) {
    return get(row, col);
}

//Mat4 Mat4::operator*(Mat4 & mat) {
//    Mat4 result;
//    for (int row = 0; row < 4; row++) {
//        for (int col = 0; col < 4; col++) {
//            float sum = 0.0f;
//            for (int i = 0; i < 4; i++) {
//                sum += get(row, i) * mat(i, col);
//            }
//            result(row, col) = sum;
//        }
//    }
//    return result;
//}

Mat4 Mat4::operator*(Mat4 mat) {
    Mat4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0.0f;
            for (int i = 0; i < 4; i++) {
                sum += get(row, i) * mat(i, col);
            }
            result(row, col) = sum;
        }
    }
    return result;
}

Vec4 Mat4::operator*(Vec4 vector) {
    Vec4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result[row] += get(row, col) * vector[col];
        }
    }
    return result;
}

Vec4 Mat4::operator*(const Vec3 & vector) {
    return *this * Vec4(vector.x, vector.y, vector.z, 1.0f);
}

float &Mat4::get(int row, int col) {
    return elements[4 * row + col];
}

Mat4 Mat4::rotateX(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix(1, 1) = cosf(rotation);
    rotationMatrix(1, 2) = -sinf(rotation);
    rotationMatrix(2, 1) = sinf(rotation);
    rotationMatrix(2, 2) = cosf(rotation);
    return rotationMatrix * *this;
}

Mat4 Mat4::rotateY(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix(0, 0) = cosf(rotation);
    rotationMatrix(0, 2) = sinf(rotation);
    rotationMatrix(2, 0) = -sinf(rotation);
    rotationMatrix(2, 2) = cosf(rotation);
    return rotationMatrix * *this;
}

Mat4 Mat4::rotateZ(float rotation) {
    Mat4 rotationMatrix;
    rotationMatrix(0, 0) = cosf(rotation);
    rotationMatrix(0, 1) = -sinf(rotation);
    rotationMatrix(1, 0) = sinf(rotation);
    rotationMatrix(1, 1) = cosf(rotation);
    return rotationMatrix * *this;
}

Mat4 Mat4::rotate(const Vec3 &rotation) {
    return rotateZ(rotation.z).rotateY(rotation.y).rotateX(rotation.x);
}

Vec3 Mat4::getPosition() {
    return Vec3(get(0, 3), get(1, 3), get(2, 3));
}

Mat4 &Mat4::translate(const Vec3 & translation) {
    get(0, 3) += translation.x;
    get(1, 3) += translation.y;
    get(2, 3) += translation.z;
    return *this;
}

Mat4 & Mat4::setPosition(const Vec3 & position) {
    get(0, 3) = position.x;
    get(1, 3) = position.y;
    get(2, 3) = position.z;
    return *this;
}

Mat4 &Mat4::scalePosition(Vec3 scale) {
    get(0, 3) *= scale.x;
    get(1, 3) *= scale.y;
    get(2, 3) *= scale.z;

    return *this;
}

Mat4 Mat4::rotate(Quaternion &quaternion) {
    Vec3 scale = fromQuaternion(quaternion).getScale();
    return fromQuaternion(quaternion).scale(Vec3(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z)) * *this;
}

Quaternion Mat4::toQuaternion() {
    float m00 = get(0, 0);
    float m11 = get(1, 1);
    float m22 = get(2, 2);
    float trace = m00 + m11 + m22;

    if (trace > 0) {
        float s = std::sqrt(trace + 1.0f) * 2;
        float w = 0.25f * s;
        float x = (get(2, 1) - get(1, 2)) / s;
        float y = (get(0, 2) - get(2, 0)) / s;
        float z = (get(1, 0) - get(0, 1)) / s;
        return Quaternion(w, x, y, z);
    }
    if (m00 > m11 && m00 > m22) {
        float s = std::sqrt(1.0f + m00 - m11 - m22) * 2;
        float w = (get(2, 1) - get(1, 2)) / s;
        float x = 0.25f * s;
        float y = (get(0, 1) + get(1, 0)) / s;
        float z = (get(0, 2) + get(2, 0)) / s;
        return Quaternion(w, x, y, z);
    }
    if (m11 > m22) {
        float s = std::sqrt(1.0f + m11 - m00 - m22) * 2;
        float w = (get(0, 2) - get(2, 0)) / s;
        float x = (get(0, 1) + get(1, 0)) / s;
        float y = 0.25f * s;
        float z = (get(1, 2) + get(2, 1)) / s;
        return Quaternion(w, x, y, z);
    }

    float s = std::sqrt(1.0f + m22 - m00 - m11) * 2;
    float w = (get(1, 0) - get(0, 1)) / s;
    float x = (get(0, 2) + get(2, 0)) / s;
    float y = (get(1, 2) + get(2, 1)) / s;
    float z = 0.25f * s;
    return Quaternion(w, x, y, z);
}

Mat4 Mat4::fromQuaternion(Quaternion & quaternion) {
    Quaternion norm = quaternion.normal();

    float x = norm.getX();
    float y = norm.getY();
    float z = norm.getZ();
    float w = norm.getW();

    std::vector<float> elements = {
            1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
            2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
            2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x* w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    return Mat4(elements);
}

Mat4 Mat4::scale(Vec3 scale) {
    std::vector<float> elements = {
            scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    Mat4 scaleMatrix(elements);
    return *this * scaleMatrix;
}

Vec3 Mat4::getScale() {
    Vec3 x = Vec3(get(0, 0), get(1, 0), get(2, 0));
    Vec3 y = Vec3(get(0, 1), get(1, 1), get(2, 1));
    Vec3 z = Vec3(get(0, 2), get(1, 2), get(2, 2));
    return Vec3(x.length(), y.length(), z.length());
}

bool Mat4::isZeroMatrix() {
    for (int i = 0; i < elements.size() - 1; i++) {
        if (elements[i] != 0.0f) {
            return false;
        }
    }
    return true;
}

std::string Mat4::toString() {
    std::string s;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            s += std::to_string(get(i, j)) + ", ";
        }
        s+= "\n";
    }
    return s;
}

Mat4 Mat4::inverse() {
    float det = determinant();
    Mat4 adjugate;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sign = (row + col) % 2 == 0 ? 1.0f : -1.0f;
            float minor = computeMinor(4, elements, row, col);
            adjugate(col, row) = (sign * minor) / det;
        }
    }
    return adjugate;
}

float Mat4::determinant() {
    return computeDeterminant(4, elements);
}

float Mat4::computeDeterminant(int dimensions, std::vector<float> & elements) {
    if (dimensions == 0) {
        return 1.0f;
    }
    if (dimensions == 1) {
        return elements[0];
    }
    if (dimensions == 2) {
        return (elements[0] * elements[3]) - (elements[1] * elements[2]);
    } else {
        float sum = 0.0f;
        for (int col = 0; col < dimensions; col++) {
            float sign = col % 2 == 0 ? 1.0f : -1.0f;
            sum += sign * elements[col] * computeMinor(dimensions, elements, 0, col);
        }
        return sum;
    }
}

float Mat4::computeMinor(int dimensions, std::vector<float> & elements, int row, int col) {
    std::vector<float> minorElements;
    for (int r = 0; r < dimensions; r++) {
        if (r != row) {
            for (int c = 0; c < dimensions; c++) {
                if (c != col) {
                    minorElements.emplace_back(elements[dimensions * r + c]);
                }
            }
        }
    }
    return computeDeterminant(dimensions - 1, minorElements);
}

