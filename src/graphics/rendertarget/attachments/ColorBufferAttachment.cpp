#include "ColorBufferAttachment.h"

ColorBufferAttachment::ColorBufferAttachment(int index, int width, int height, bool multiSampled) : Attachment(), index(index), width(width), height(height), multiSampled(multiSampled), handle(0) {
    glGenRenderbuffers(1, &handle);
    glBindRenderbuffer(GL_RENDERBUFFER, handle);
    if (multiSampled) {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_RGBA8, width, height);
    } else {
        glRenderbufferStorage(GL_RENDER, GL_RGBA8, width, height);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, handle);
}

void ColorBufferAttachment::resize(int width, int height) {

}

Attachment::Type ColorBufferAttachment::getType() {
    return Attachment::COLOR_BUFFER;
}

void ColorBufferAttachment::init() {
    glBindRenderbuffer(GL_RENDERBUFFER, handle);
    if (multiSampled) {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_RGBA8, width, height);
    } else {
        glRenderbufferStorage(GL_RENDER, GL_RGBA8, width, height);
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, handle);
}
