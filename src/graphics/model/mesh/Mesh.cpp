#include "Mesh.h"

Mesh::Mesh(Layout & layout, char * vertices, const std::vector<GLuint> & indices) : vao(0), vbo(0), ibo(0) {

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, indices.size() * layout.getStride(), &vertices[0], GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayElementBuffer(vao, ibo);

    int offset = 0;

    for (auto & attribute : layout.getAttributes()) {
        glVertexArrayVertexBuffer(vao, attribute.getLocation(), vbo, offset, layout.getStride());
        glEnableVertexArrayAttrib(vao, attribute.getLocation());

        if (attribute.getType() == Attribute::INT) {
            glVertexArrayAttribIFormat(vao, attribute.getLocation(), attribute.getSize(), attribute.getTypeCode(), 0);
        } else {
            glVertexArrayAttribFormat(vao, attribute.getLocation(), attribute.getSize(), attribute.getTypeCode(), GL_FALSE, 0);
        }
        offset += attribute.getSize() * attribute.getTypeSize();
    }

    count = indices.size();
}

Mesh::Mesh(Layout & layout, const std::vector<GLfloat> & vertices, const std::vector<GLuint> & indices) : vao(0), vbo(0), ibo(0) {

    glCreateBuffers(1, &ibo);
    glNamedBufferData(ibo, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayElementBuffer(vao, ibo);

    int offset = 0;

    for (auto & attribute : layout.getAttributes()) {
        glVertexArrayVertexBuffer(vao, attribute.getLocation(), vbo, offset, layout.getStride());
        glEnableVertexArrayAttrib(vao, attribute.getLocation());

        if (attribute.getType() == Attribute::INT) {
            glVertexArrayAttribIFormat(vao, attribute.getLocation(), attribute.getSize(), attribute.getTypeCode(), 0);
        } else {
            glVertexArrayAttribFormat(vao, attribute.getLocation(), attribute.getSize(), attribute.getTypeCode(), GL_FALSE, 0);
        }
        offset += attribute.getSize() * attribute.getTypeSize();
    }

    count = indices.size();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::render() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

