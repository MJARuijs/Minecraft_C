#pragma once

class ImageData {

private:
    int width;
    int height;
    unsigned char * data;

public:
    ImageData(int width, int height, unsigned char * data);
    ~ImageData();

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] unsigned char *getData() const;
};