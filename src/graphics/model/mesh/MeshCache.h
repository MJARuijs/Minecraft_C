#pragma once

#include <map>
#include "Mesh.h"
#include "MeshLoader.h"

class MeshCache {

private:
    static std::map<std::string, Mesh*> cache;
    static MeshLoader loader;

public:
    static Mesh * get(const std::string & path);
    static Mesh * get(const std::string & path, aiMesh * aiMesh);

};