#pragma once

#include <GL/glew.h>
#include <string>
#include "../../resources/images/ImageData.h"

class ImageMap {

private:
    GLuint handle{};

public:
    explicit ImageMap(ImageData * data);
    ImageMap();
    ~ImageMap();

    [[nodiscard]] GLuint getHandle() const;


};