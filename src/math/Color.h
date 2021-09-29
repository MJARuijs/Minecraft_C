#pragma once

#include "vectors/Vec3.h"
#include <string>

class Color {

private:
    float r;
    float g;
    float b;
    float a;

public:

    explicit Color(float r, float g, float b, float a);
    Color(float r, float g, float b);
    Color(int r, int g, int b, int a);
    Color(int r, int g, int b);
    Color(const Color & otherColor);
    Color();

    void setR(float newR);
    void setG(float newG);
    void setB(float newB);
    void setA(float newA);

    float getR() const;
    float getG() const;
    float getB() const;
    float getA() const;

    bool operator==(Color & other) const;
    float & operator[](int i);
    float & get(int i);
    Color & set(int i, float value);
    Color operator+(Color & other) const;
    Color operator-() const;
    Color operator*(float scale) const;

    Vec3 rgb() const;
    Color copy() const;

    std::string toString();

};