#include "ChunkMesh.h"

ChunkMesh::ChunkMesh(const std::vector<float> & vertices, int vertexCount) : vao(0), vbo(0), vertexCount(vertexCount) {
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    glNamedBufferData(vbo, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 24);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayVertexBuffer(vao, 1, vbo, 12, 24);
    glVertexArrayAttribIFormat(vao, 1, 1, GL_FLOAT, 0);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayVertexBuffer(vao, 2, vbo, 16, 24);
    glVertexArrayAttribIFormat(vao, 2, 1, GL_FLOAT, 0);
    glEnableVertexArrayAttrib(vao, 2);

    glVertexArrayVertexBuffer(vao, 3, vbo, 20, 24);
    glVertexArrayAttribIFormat(vao, 3, 1, GL_FLOAT, 0);
    glEnableVertexArrayAttrib(vao, 3);
}

ChunkMesh::ChunkMesh(char * vertices, int vertexCount) : vao(0), vbo(0), vertexCount(vertexCount) {
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    glNamedBufferData(vbo, vertexCount * 4 * 6, &vertices[0], GL_DYNAMIC_DRAW);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 24);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayVertexBuffer(vao, 1, vbo, 12, 24);
    glVertexArrayAttribIFormat(vao, 1, 1, GL_INT, 0);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayVertexBuffer(vao, 2, vbo, 16, 24);
    glVertexArrayAttribIFormat(vao, 2, 1, GL_INT, 0);
    glEnableVertexArrayAttrib(vao, 2);

    glVertexArrayVertexBuffer(vao, 3, vbo, 20, 24);
    glVertexArrayAttribIFormat(vao, 3, 1, GL_INT, 0);
    glEnableVertexArrayAttrib(vao, 3);
}

ChunkMesh::~ChunkMesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void ChunkMesh::updateInstanceData(char * vertices, int count) {
    vertexCount = count;
    glNamedBufferData(vbo, count * 4 * 6, &vertices[0], GL_DYNAMIC_DRAW);
}

void ChunkMesh::render() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
