#include "StaticModelCache.h"
#include "StaticModelLoader.h"

std::map<std::string, StaticModel*> StaticModelCache::cache = {};

StaticModelLoader StaticModelCache::loader = StaticModelLoader();

StaticModel *StaticModelCache::get(const std::string &path) {
    for (auto & it : cache) {
        if (it.first == path) {
            return it.second;
        }
    }

    StaticModel * model = StaticModelLoader::load(path);
    cache[path] = model;
    return model;
}
