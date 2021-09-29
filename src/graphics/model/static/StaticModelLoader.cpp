#include "StaticModelLoader.h"
#include "../mesh/MeshCache.h"

StaticModel * StaticModelLoader::load(const std::string &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_OptimizeGraph);

    if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("Something bad went wrong..");
    }

    StaticModel * model = createModel(filePath, scene->mRootNode, scene);
    return model;
}

StaticModel * StaticModelLoader::createModel(const std::string & path, aiNode *node, const aiScene *scene) {
    std::vector<Shape*> shapes;
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh * aiMesh = scene->mMeshes[node->mMeshes[i]];
        aiMaterial * aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];
        aiColor4D diffuse;
        aiColor4D specular;
        float shininess;
        aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
        aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_SPECULAR, &specular);
        aiGetMaterialFloat(aiMaterial, AI_MATKEY_SHININESS, &shininess);

        Material material(convertColor(diffuse), convertColor(specular), shininess);
        Mesh * mesh = MeshCache::get(path, aiMesh);
        shapes.push_back(new Shape(*mesh, material));
    }

    return new StaticModel(shapes);
}

Color StaticModelLoader::convertColor(const aiColor4D& color) {
    return Color(color.r, color.g, color.b, color.a);
}
