#pragma once

#include "../../math/vectors/Vec4.h"

class MetaData {

private:
    int size;
    Vec4 padding;
    int lineHeight;
    int base;
    int scaleW;
    int scaleH;

public:
    MetaData(int size, const Vec4 &padding, int lineHeight, int base, int scaleW, int scaleH);

    [[nodiscard]] int getSize() const;

    [[nodiscard]] const Vec4 &getPadding() const;

    [[nodiscard]] int getLineHeight() const;

    [[nodiscard]] int getBase() const;

    [[nodiscard]] int getScaleW() const;

    [[nodiscard]] int getScaleH() const;

    float getPaddingTop();
    float getPaddingRight();
    float getPaddingBottom();
    float getPaddingLeft();

    float getPaddingWidth();
    float getPaddingHeight();
};