#pragma once

#include <string>
#include "../../math/vectors/Vec2.h"
#include "../../math/vectors/Vec3.h"
#include "../../math/Color.h"
#include <GL/glew.h>
#include <stdexcept>
#include <iostream>
#include "Shader.h"
#include "../../math/matrices/Mat4.h"

class ShaderProgram {

private:
    GLuint handle;

public:
    ShaderProgram(const std::string & vertexPath, const std::string & geometryPath, const std::string & fragmentPath);
    ShaderProgram(const std::string & vertexPath, const std::string & fragmentPath);
    ~ShaderProgram();

    void start() const;
    static void stop() ;

    void set(const char * name, int value) const;
    void set(const char * name, float value) const;
    void set(const char * name, const Vec2 & vector) const;
    void set(const char * name, const Vec3 & vector) const;
    void set(const char * name, Mat4  matrix) const;
    void set(const char * name, const Color & color) const;

};
