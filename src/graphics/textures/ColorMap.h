#pragma once

#include <GL/glew.h>

class ColorMap {

private:
    int width;
    int height;
    bool multiSampled;
    GLuint handle;

public:
    ColorMap(int width, int height, bool multiSampled);
    ColorMap(int width, int height);
    ~ColorMap();

    void init() const;

    [[nodiscard]] GLuint getHandle() const;

};