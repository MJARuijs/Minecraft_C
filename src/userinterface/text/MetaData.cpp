#include "MetaData.h"

MetaData::MetaData(int size, const Vec4 &padding, int lineHeight, int base, int scaleW, int scaleH) : size(size),
                                                                                                      padding(padding),
                                                                                                      lineHeight(lineHeight),
                                                                                                      base(base),
                                                                                                      scaleW(scaleW),
                                                                                                      scaleH(scaleH) {}

int MetaData::getSize() const {
    return size;
}

const Vec4 &MetaData::getPadding() const {
    return padding;
}

int MetaData::getLineHeight() const {
    return lineHeight;
}

int MetaData::getBase() const {
    return base;
}

int MetaData::getScaleW() const {
    return scaleW;
}

int MetaData::getScaleH() const {
    return scaleH;
}

float MetaData::getPaddingTop() {
    return padding[0];
}

float MetaData::getPaddingRight() {
    return padding[1];
}

float MetaData::getPaddingBottom() {
    return padding[2];
}

float MetaData::getPaddingLeft() {
    return padding[3];
}

float MetaData::getPaddingWidth() {
    return getPaddingLeft() + getPaddingRight();
}

float MetaData::getPaddingHeight() {
    return getPaddingTop() + getPaddingBottom();
}
