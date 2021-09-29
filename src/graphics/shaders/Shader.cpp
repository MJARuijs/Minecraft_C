#include <stdexcept>
#include "Shader.h"
#include "../../util/FileReader.h"

Shader::Shader(GLenum type, const std::string & filePath) {

    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER && type != GL_COMPUTE_SHADER && type != GL_GEOMETRY_SHADER) {
        throw std::runtime_error("Invalid shader type!");
    }

    handle = glCreateShader(type);

    std::string shaderCode = FileReader::getContent(filePath);

    const GLchar * sourcePointer = shaderCode.c_str();

    glShaderSource(handle, 1, &sourcePointer, nullptr);
    glCompileShader(handle);

    GLint compiled;

    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
        GLint length;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
        auto * log = (GLchar*)malloc(static_cast<size_t>(length));
        glGetShaderInfoLog(handle, length, nullptr, log);
        std::cout << log << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(handle);
}

GLuint Shader::getHandle() {
    return handle;
}
