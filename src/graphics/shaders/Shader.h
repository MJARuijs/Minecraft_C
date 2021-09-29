#pragma once

#include <GL/glew.h>
#include <string>

class Shader {

private:
    GLuint handle;

public:
    Shader(GLenum type, const std::string & filePath);
    ~Shader();

    GLuint getHandle();
};
