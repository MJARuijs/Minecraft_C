#include "AnimatedModelCache.h"

std::map<std::string, AnimatedModel*> AnimatedModelCache::cache = {};

AnimatedModelLoader AnimatedModelCache::loader = AnimatedModelLoader();

AnimatedModel * AnimatedModelCache::get(const std::string &path) {
    for (auto & it : cache) {
        if (it.first == path) {
            return it.second;
        }
    }

    AnimatedModel * model = loader.load(path);
    cache[path] = model;
    return model;
}