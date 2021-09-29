#include "RenderEngine.h"
#include "../rendertarget/RenderTargetManager.h"

RenderEngine::RenderEngine(bool multiSampled) : multiSampled(multiSampled), forwardEngine(multiSampled), deferredEngine(multiSampled) {}

void RenderEngine::render(Camera &camera, AmbientLight &ambient, Sun &sun, Skybox &skybox,
                          const std::vector<RenderData> &renderData) {

    RenderTarget * forwardTarget = forwardEngine.prepare();
    RenderTarget * geometryTarget = deferredEngine.render(camera, ambient, sun, renderData, forwardTarget);

    RenderTarget * forwardResultTarget = forwardEngine.render(camera, ambient, sun, skybox, renderData, geometryTarget);
    forwardResultTarget->renderToScreen(GL_COLOR_BUFFER_BIT);
}
