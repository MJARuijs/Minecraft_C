#include "TextQuad.h"

TextQuad::TextQuad(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textureCoords) : count(vertices.size()), vao(0), vbo(0), tbo(0), vertices(vertices) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &tbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), &textureCoords[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextQuad::~TextQuad() {
    glDeleteBuffers(1, &tbo);
    tbo = 0;

    glDeleteBuffers(1, &vbo);
    vbo = 0;

    glDeleteVertexArrays(1, &vao);
    vao = 0;
}

void TextQuad::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count / 2);
    glBindVertexArray(0);
}
