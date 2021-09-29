#pragma once

#include <GL/glew.h>
#include <vector>
#include "attachments/Attachment.h"
#include "../textures/ColorMap.h"
#include "../textures/DepthMap.h"
#include "attachments/ColorTextureAttachment.h"

class RenderTarget {

private:
    int width;
    int height;
    bool multiSampled;
    int numberOfColorTextures;
    int numberOfColorBuffers;
    bool hasDepthTexture;
    bool hasDepthBuffer;
    GLuint handle;
    bool available;

    GLuint depthTextureHandle;
    GLuint depthBufferHandle;

    std::vector<Attachment *> attachments;

    void init();
    void renderTo(int targetHandle, int buffers) const;

public:
    RenderTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers,
                 bool hasDepthTexture, bool hasDepthBuffer);

    RenderTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers,
                 bool hasDepthTexture, bool hasDepthBuffer, GLuint handle);

    ~RenderTarget();

    [[nodiscard]] GLuint getHandle() const;

    void renderToScreen(int buffers);

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] float getAspectRatio() const;

    GLuint getColorMap(int index);
    [[nodiscard]] GLuint getDepthTexture() const;

    void start();
    static void clear();
    void stop();

    void renderTo(RenderTarget & renderTarget, int buffers);

    [[nodiscard]] bool matches(int width, int height, bool multiSampled, int requiredNumberOfColorTextures, int requiredNumberOfColorBuffers, bool requiresDepthTexture, bool requiresDepthBuffer) const;

};