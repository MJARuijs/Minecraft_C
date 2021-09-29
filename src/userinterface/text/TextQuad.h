#pragma once

#include <GL/glew.h>
#include <vector>

class TextQuad {

private:
    std::vector<GLfloat> vertices;
    GLuint vao;
    GLuint vbo;
    GLuint tbo;
    int count;

public:
    TextQuad(const std::vector<GLfloat> & vertices, const std::vector<GLfloat> & textureCoords);
    ~TextQuad();
    void draw() const;
};