#include "RenderTargetManager.h"

std::vector<RenderTarget*> RenderTargetManager::renderTargets = {};

int RenderTargetManager::width = 0;
int RenderTargetManager::height = 0;

void RenderTargetManager::init(int width, int height) {
    RenderTargetManager::width = width;
    RenderTargetManager::height = height;
}

RenderTarget * RenderTargetManager::getAvailableTarget(bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer) {
    return getAvailableTarget(width, height, multiSampled, numberOfColorTextures, numberOfColorBuffers, hasDepthTexture, hasDepthBuffer);
}

RenderTarget * RenderTargetManager::getAvailableTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer) {
    for (auto & target : renderTargets) {
        if (target->matches(width, height, multiSampled, numberOfColorTextures, numberOfColorBuffers, hasDepthTexture, hasDepthBuffer)) {
            return target;
        }
    }

    RenderTarget * newTarget = createTarget(width, height, multiSampled, numberOfColorTextures, numberOfColorBuffers, hasDepthTexture, hasDepthBuffer);
    renderTargets.emplace_back(newTarget);
    return renderTargets.back();
}

RenderTarget * RenderTargetManager::createTarget(int width, int height, bool multiSampled, int numberOfColorTextures, int numberOfColorBuffers, bool hasDepthTexture, bool hasDepthBuffer) {
    return new RenderTarget(width, height, multiSampled, numberOfColorTextures, numberOfColorBuffers, hasDepthTexture, hasDepthBuffer);
}

int RenderTargetManager::getWidth() {
    return width;
}

int RenderTargetManager::getHeight() {
    return height;
}
