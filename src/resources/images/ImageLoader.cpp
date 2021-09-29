#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "ImageLoader.h"

ImageData * ImageLoader::load(const std::string &path) {
    int width, height, channels;
    unsigned char * data;
    data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data) {
        throw std::runtime_error("Failed to load image: " + std::string(stbi_failure_reason()) + ": " + path);
    }

    return new ImageData(width, height, data);
}
