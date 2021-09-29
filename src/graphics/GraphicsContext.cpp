#include <stdexcept>
#include "GraphicsContext.h"

void GraphicsContext::init(const Color & color) {
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glClearColor(color.getR(), color.getG(), color.getB(), 1.0f);
}

void GraphicsContext::enable(GraphicsContext::Option option) {
    glEnable(getCode(option));
}

void GraphicsContext::disable(GraphicsContext::Option option) {
    glDisable(getCode(option));
}

int GraphicsContext::getCode(GraphicsContext::Option option) {
    switch(option) {
        case FACE_CULLING:
            return GL_CULL_FACE;
        case DEPTH_TESTING:
            return GL_DEPTH_TEST;
        case ALPHA_BLENDING:
            return GL_BLEND;
        case TEXTURE_MAPPING:
            return GL_TEXTURE;
        case MULTI_SAMPLE:
            return GL_MULTISAMPLE;
        case DEPTH_BUFFER_BIT:
            return GL_DEPTH_BUFFER_BIT;
        case COLOR_BUFFER_BIT:
            return GL_COLOR_BUFFER_BIT;
    }
    return -1;
}
