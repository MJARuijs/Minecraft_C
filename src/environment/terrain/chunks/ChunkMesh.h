#pragma once

#include <GL/glew.h>
#include <vector>

class ChunkMesh {

private:
    GLuint vao;
    GLuint vbo;
    int vertexCount;

public:
    ChunkMesh(char * vertices, int vertexCount);
    ChunkMesh(const std::vector<float> & vertices, int vertexCount);
    ~ChunkMesh();

    void updateInstanceData(char * vertices, int count);
    void render() const;
};