#pragma once

#include <vector>
#include <GL/glew.h>
#include "Layout.h"

class Mesh {

private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLsizei count;

public:
    Mesh(Layout & layout, char * vertices, const std::vector<GLuint> & indices);
    Mesh(Layout & layout, const std::vector<GLfloat> & vertices, const std::vector<GLuint> & indices);
    ~Mesh();

    void render() const;
};