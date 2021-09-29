#include "TextureArray.h"

#include <cmath>
#include <GL/glew.h>

TextureArray::TextureArray(const std::vector<ImageData *> & textures) : handle(0) {
    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &handle);

    int width = textures[0]->getWidth();
    int height = textures[0]->getHeight();

    float size = std::min(width, height);
    int levels = (int)fmax(1, std::log2(size));

    glTextureStorage3D(handle, levels, GL_RGBA8, width, height, textures.size());

    for (int i = 0; i < textures.size(); i++) {
        ImageData * texture = textures[i];
        glTextureSubImage3D(handle, 0, 0, 0, i, texture->getWidth(), texture->getHeight(), 1, GL_RGBA, GL_UNSIGNED_BYTE, texture->getData());
    }

    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float maxAnisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
    glTextureParameterf(handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

    glGenerateTextureMipmap(handle);
}

GLuint TextureArray::getHandle() const {
    return handle;
}
