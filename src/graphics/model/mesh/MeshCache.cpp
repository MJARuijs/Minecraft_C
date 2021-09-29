#include "MeshCache.h"

std::map<std::string, Mesh*> MeshCache::cache = {};

MeshLoader MeshCache::loader = MeshLoader();

Mesh *MeshCache::get(const std::string &path) {
    for (auto & it : cache) {
        if (it.first == path) {
            return it.second;
        }
    }

    Mesh * mesh = loader.load(path);
    cache[path] = mesh;
    return mesh;
}

Mesh *MeshCache::get(const std::string & path, aiMesh *aiMesh) {
    for (auto & it : cache) {
        if (it.first == path) {
            return it.second;
        }
    }

    Mesh * mesh = loader.load(aiMesh);
    cache[path] = mesh;
    return mesh;
}
