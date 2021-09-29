#pragma once

#include <GL/glew.h>

class DepthMap {

private:
    int width;
    int height;
    bool multiSampled;
    GLuint handle;

public:
    DepthMap(int width, int height, bool multiSampled);
    ~DepthMap();

    void init() const;

    [[nodiscard]] GLuint getHandle() const;
};