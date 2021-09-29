#pragma once

#include <cmath>
#include <vector>
#include "../vectors/Vec3.h"
#include "../vectors/Vec4.h"
#include "../Quaternion.h"

class Mat4 {

private:
    std::vector<float> elements;

public:
    Mat4();

    explicit Mat4(std::vector<float> elements);
    explicit Mat4(float scale);

    float & operator() (int row, int col);
    float & get(int row, int col);

    Mat4 operator* (Mat4 mat);
//    Mat4 operator* (Mat4 & mat);
    Vec4 operator* (Vec4 vector);
    Vec4 operator* (const Vec3 & vector);

    Mat4 rotateX(float rotation);
    Mat4 rotateY(float rotation);
    Mat4 rotateZ(float rotation);
    Mat4 rotate(const Vec3 & rotation);
    Mat4 rotate(Quaternion & quaternion);

    Vec3 getPosition();
    Mat4 & translate(const Vec3 & translation);
    Mat4 & setPosition(const Vec3 & position);
    Mat4 & scalePosition(Vec3 scale);

    Vec3 getScale();
    Mat4 scale(Vec3 scale);

    Mat4 inverse();
    float determinant();
    float computeDeterminant(int dimensions, std::vector<float> & elements);
    float computeMinor(int dimensions, std::vector<float> & elements, int row, int col);

    bool isZeroMatrix();

    Quaternion toQuaternion();

    std::string toString();

    static Mat4 fromQuaternion(Quaternion & quaternion);

};