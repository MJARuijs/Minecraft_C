#include "ImageData.h"

ImageData::ImageData(int width, int height, unsigned char *data) : width(width), height(height), data(data) {}

int ImageData::getWidth() const {
    return width;
}

int ImageData::getHeight() const {
    return height;
}

unsigned char *ImageData::getData() const {
    return data;
}

ImageData::~ImageData() {
    delete data;
}
