#include <GL/glew.h>
#include <cmath>
#include "ImageMap.h"

ImageMap::ImageMap(ImageData * data) : handle(0) {
    glCreateTextures(GL_TEXTURE_2D, 1, &handle);

    int size = std::min(data->getWidth(), data->getHeight());
    int levels = (int)fmax(1, std::log2(size));

    glTextureStorage2D(handle, levels, GL_RGBA8, data->getWidth(), data->getHeight());
    glTextureSubImage2D(handle, 0, 0, 0, data->getWidth(), data->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, data->getData());


    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateTextureMipmap(handle);

    float maxAnisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
    glTextureParameterf(handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
}

ImageMap::ImageMap() : handle(0) {}

ImageMap::~ImageMap() {
    glDeleteTextures(1, &handle);
}

GLuint ImageMap::getHandle() const {
    return handle;
}
