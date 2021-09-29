#include "ShaderProgram.h"
#include "../../util/Logger.h"

ShaderProgram::ShaderProgram(const std::string & vertexPath, const std::string & fragmentPath) {
    handle = glCreateProgram();

    Shader vertexShader(GL_VERTEX_SHADER, vertexPath);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentPath);

    glAttachShader(handle, vertexShader.getHandle());
    glAttachShader(handle, fragmentShader.getHandle());

    glLinkProgram(handle);
    glValidateProgram(handle);

    GLint result;

    glGetProgramiv(handle, GL_VALIDATE_STATUS, &result);

    GLint linked = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);

    if (linked != GL_TRUE) {
        GLint size;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);

        GLchar log[size];
        glGetProgramInfoLog(handle, size, &size, log);

        glDeleteProgram(handle);
        throw std::runtime_error("Could not link program: \n" + std::string(log));
    }
}


ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &geometryPath,
                             const std::string &fragmentPath) {
    handle = glCreateProgram();

    Shader vertexShader(GL_VERTEX_SHADER, vertexPath);
    Shader geometryShader(GL_GEOMETRY_SHADER, geometryPath);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentPath);

    glAttachShader(handle, vertexShader.getHandle());
    glAttachShader(handle, geometryShader.getHandle());
    glAttachShader(handle, fragmentShader.getHandle());

    glLinkProgram(handle);
    glValidateProgram(handle);

    GLint result;

    glGetProgramiv(handle, GL_VALIDATE_STATUS, &result);

    GLint linked = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);

    if (linked != GL_TRUE) {
        GLint size;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &size);

        GLchar log[size];
        glGetProgramInfoLog(handle, size, &size, log);

        glDeleteProgram(handle);
        throw std::runtime_error("Could not link program: \n" + std::string(log));
    }
}

ShaderProgram::~ShaderProgram() {
    stop();
    glDeleteProgram(handle);
}

void ShaderProgram::start() const {
    glUseProgram(handle);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::set(const char * name, int value) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniform1i(location, value);
}

void ShaderProgram::set(const char * name, float value) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniform1f(location, value);
}

void ShaderProgram::set(const char * name, const Vec2 & vector) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::set(const char * name, const Vec3 & vector) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::set(const char *name, Mat4 matrix) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniformMatrix4fv(location, 1, GL_TRUE, &matrix(0, 0));
}

void ShaderProgram::set(const char *name, const Color &color) const {
    GLint location = glGetUniformLocation(handle, name);
    glUniform4f(location, color.getR(), color.getG(), color.getB(), color.getA());
}
