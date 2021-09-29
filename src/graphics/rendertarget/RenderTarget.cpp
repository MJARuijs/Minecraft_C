#include <stdexcept>
#include <iostream>
#include "RenderTarget.h"
#include "attachments/ColorTextureAttachment.h"
#include "attachments/ColorBufferAttachment.h"

RenderTarget::RenderTarget(int width, int height, bool multiSampled, int numberOfColorTextures,
                           int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer, GLuint handle) : width(width), height(height), multiSampled(multiSampled),
                                                                                                            numberOfColorTextures(numberOfColorTextures),
                                                                                                            numberOfColorBuffers(numberOfColorBuffers),
                                                                                                            hasDepthTexture(hasDepthTexture),
                                                                                                            hasDepthBuffer(hasDepthBuffer),
                                                                                                            handle(handle),
                                                                                                            depthBufferHandle(-1),
                                                                                                            depthTextureHandle(-1),
                                                                                                            available(true) {
    init();
}

RenderTarget::RenderTarget(int width, int height, bool multiSampled, int numberOfColorTextures,
                           int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer) : width(width), height(height), multiSampled(multiSampled),
                                                                                                                            numberOfColorTextures(numberOfColorTextures),
                                                                                                                            numberOfColorBuffers(numberOfColorBuffers),
                                                                                                                            hasDepthTexture(hasDepthTexture),
                                                                                                                            hasDepthBuffer(hasDepthBuffer),
                                                                                                                            handle(0),
                                                                                                                            depthBufferHandle(-1),
                                                                                                                            depthTextureHandle(-1),
                                                                                                                            available(true) {
    glCreateFramebuffers(1, &handle);
    init();
}

RenderTarget::~RenderTarget() {
    glDeleteFramebuffers(1, &handle);
}

int RenderTarget::getWidth() const {
    return width;
}

int RenderTarget::getHeight() const {
    return height;
}

float RenderTarget::getAspectRatio() const {
    return (float)width / (float)height;
}

GLuint RenderTarget::getColorMap(int index) {
    for (auto & attachment : attachments) {
        if (attachment->getType() == Attachment::COLOR_TEXTURE) {
            if (reinterpret_cast<ColorTextureAttachment *>(attachment)->getIndex() == index) {
                return reinterpret_cast<ColorTextureAttachment *>(attachment)->getColorMap().getHandle();
            }
        }
    }
    throw std::runtime_error("This RenderTarget does not have a ColorTexture Attachment that matches the requested index!");
}

GLuint RenderTarget::getDepthTexture() const {
    if (hasDepthTexture) {
        return depthTextureHandle;
    }
    throw std::runtime_error("This RenderTarget does not have a DepthTexture Attachment!");
}

void RenderTarget::start() {
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
    glViewport(0, 0, width, height);
    available = false;
}

void RenderTarget::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTarget::stop() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    available = true;
}

void RenderTarget::renderTo(int targetHandle, int buffers) const {
    if (targetHandle == this->handle) {
        return;
    }

    glBlitNamedFramebuffer(handle, targetHandle, 0, 0, width, height, 0, 0, width, height, buffers, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::renderTo(RenderTarget &renderTarget, int buffers) {
    renderTo(renderTarget.handle, buffers);
}

void RenderTarget::renderToScreen(int buffers) {
    renderTo(0, buffers);
}

bool RenderTarget::matches(int width, int height, bool multiSampled, int requiredNumberOfColorTextures, int requiredNumberOfColorBuffers,
                      bool requiredDepthTexture, bool requiresDepthBuffer) const {

    if (width != this->width) return false;
    if (height != this->height) return false;
    if (multiSampled != this->multiSampled) return false;

    if (this->numberOfColorTextures != requiredNumberOfColorTextures) return false;
    if (this->numberOfColorBuffers != requiredNumberOfColorBuffers) return false;
    if (this->hasDepthTexture != requiredDepthTexture) return false;
    if (this->hasDepthBuffer != requiresDepthBuffer) return false;

    return true;
}

void RenderTarget::init() {
    glBindFramebuffer(GL_FRAMEBUFFER, handle);

    int colorCounter = 0;

    for (int i = 0; i < numberOfColorTextures; i++) {
        attachments.emplace_back(new ColorTextureAttachment(colorCounter++, width, height, multiSampled));
    }

    for (int i = 0; i < numberOfColorBuffers; i++) {
        attachments.emplace_back(new ColorBufferAttachment(colorCounter++, width, height, multiSampled));
    }

    GLenum drawBuffers[colorCounter];

    for (int i = 0; i < colorCounter; i++) {
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    glDrawBuffers(colorCounter, drawBuffers);

    if (hasDepthTexture) {
        glGenTextures(1, &depthTextureHandle);
        if (multiSampled) {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthTextureHandle);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_DEPTH_COMPONENT32, width, height, true);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depthTextureHandle, 0);
        } else {
            glBindTexture(GL_TEXTURE_2D, depthTextureHandle);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureHandle, 0);
        }
    }

    if (hasDepthBuffer) {
        GLuint depthRenderBuffer;
        glGenRenderbuffers(1, &depthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);

        if (multiSampled) {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_DEPTH_COMPONENT, width, height);
        } else {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        }
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTarget::getHandle() const {
    return handle;
}
