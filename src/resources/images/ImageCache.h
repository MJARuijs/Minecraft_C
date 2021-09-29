#pragma once

#include <string>
#include <map>
#include "../../graphics/textures/ImageMap.h"
#include "ImageLoader.h"

class ImageCache {

private:
    static std::map<std::string, ImageData*> cache;

public:
    static ImageData * get(const std::string & path);
};