#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "StaticModel.h"
#include "../mesh/MeshLoader.h"

class StaticModelLoader {

private:
    static StaticModel * createModel(const std::string & path, aiNode * node, const aiScene * scene);
    static Color convertColor(const aiColor4D& color);

public:
    StaticModelLoader() = default;
    static StaticModel * load(const std::string & filePath);


};