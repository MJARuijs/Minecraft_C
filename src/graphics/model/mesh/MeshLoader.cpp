
#include <stdexcept>
#include <iostream>
#include "MeshLoader.h"

Mesh *MeshLoader::load(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeGraph);
    if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("Something bad went wrong..");
    }
    aiMesh ** meshes = scene->mMeshes;
    return load(meshes[0]);
}

Mesh *MeshLoader::load(aiMesh *aiMesh) {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    std::vector<Attribute> attributes;

    attributes.emplace_back(Attribute(0, 3));

    if (aiMesh->mNormals) {
        attributes.emplace_back(Attribute(1, 3));
    }

    if (aiMesh->mTextureCoords[0]) {
        attributes.emplace_back(Attribute(2, 2));
    }

    for (int i = 0; i < aiMesh->mNumVertices; i++) {
        vertices.push_back(aiMesh->mVertices[i].x);
        vertices.push_back(aiMesh->mVertices[i].y);
        vertices.push_back(aiMesh->mVertices[i].z);

        vertices.push_back(aiMesh->mNormals[i].x);
        vertices.push_back(aiMesh->mNormals[i].y);
        vertices.push_back(aiMesh->mNormals[i].z);

        if (aiMesh->mTextureCoords[0]) {
            vertices.push_back(aiMesh->mTextureCoords[0][i].x);
            vertices.push_back(aiMesh->mTextureCoords[0][i].y);
        }
    }

    for (int i = 0; i < aiMesh->mNumFaces; i++) {
        aiFace face = aiMesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Layout layout(attributes);
    return new Mesh(layout, vertices, indices);
}
