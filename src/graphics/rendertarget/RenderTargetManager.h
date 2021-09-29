#pragma once

#include <vector>
#include "RenderTarget.h"

class RenderTargetManager {

private:
    static std::vector<RenderTarget*> renderTargets;
    static int width;
    static int height;
    static RenderTarget * createTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer);

public:
    static void init(int width, int height);

    static int getWidth();
    static int getHeight();

    static RenderTarget * getAvailableTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer);
    static RenderTarget * getAvailableTarget(bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer);

};