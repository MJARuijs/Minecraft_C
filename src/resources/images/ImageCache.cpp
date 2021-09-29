#include <iostream>
#include "ImageCache.h"

std::map<std::string, ImageData*> ImageCache::cache;

ImageData * ImageCache::get(const std::string & path) {
    if (cache.find(path) != cache.end()) {
        return cache[path];
    }

    cache[path] = ImageLoader::load(path);
    return cache[path];
}
