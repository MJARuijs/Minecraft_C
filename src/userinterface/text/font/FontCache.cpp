#include "FontCache.h"
#include "FontLoader.h"

std::map<std::string, Font*> FontCache::cache;

Font *FontCache::get(const std::string &path, float aspectRatio) {
    if (cache.find(path) != cache.end()) {
        return cache[path];
    }

    cache[path] = FontLoader::load(path, aspectRatio);
    return cache[path];
}
