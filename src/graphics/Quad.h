#pragma once

#include <GL/glew.h>
#include <vector>

class Quad {

private:
    GLuint vao;
    GLuint vbo;

    std::vector<GLfloat> vertices = {
            -1.0f, 1.0f,
            -1.0f, -1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            -1.0f, -1.0f,
            1.0f, -1.0f
    };

public:
    Quad() : vao(0), vbo(0) {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Quad() {
        glDeleteBuffers(1, &vbo);
        vbo = 0;

        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    void draw() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);
    }

};