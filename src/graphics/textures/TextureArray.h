#pragma once

#include <vector>
#include <GL/glew.h>
#include <cmath>
#include "../../resources/images/ImageData.h"

class TextureArray {

private:
    GLuint handle;

public:
    explicit TextureArray(const std::vector<ImageData*> & textures);

    [[nodiscard]] GLuint getHandle() const;
};