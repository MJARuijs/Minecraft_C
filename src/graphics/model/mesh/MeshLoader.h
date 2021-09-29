#pragma once

#include <string>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Mesh.h"

class MeshLoader {

public:
    MeshLoader() = default;

    static Mesh * load(const std::string & path);
    static Mesh * load(aiMesh * aiMesh);
};