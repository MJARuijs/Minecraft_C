#include "ForwardRenderEngine.h"
#include "../rendertarget/RenderTargetManager.h"

ForwardRenderEngine::ForwardRenderEngine(bool multiSampled) : multiSampled(multiSampled), forwardTarget(nullptr) {}

ForwardRenderEngine::~ForwardRenderEngine() {
    delete forwardTarget;
}

RenderTarget * ForwardRenderEngine::prepare() {
    forwardTarget = RenderTargetManager::getAvailableTarget(multiSampled, 1, 0, true, false);
    return forwardTarget;
}

RenderTarget * ForwardRenderEngine::render(Camera &camera, AmbientLight &ambient, Sun &sun, Skybox &skyBox,
                                 const std::vector<RenderData> &renderData, RenderTarget *geometryTarget) {

    bool containsDeferredItems = false;
    for (auto & data : renderData) {
        if (data.getType() == DEFERRED) {
            containsDeferredItems = true;
            break;
        }
    }

    if (containsDeferredItems) {
        geometryTarget->renderTo(*forwardTarget, GL_DEPTH_BUFFER_BIT);
        forwardTarget->start();
    } else {
        forwardTarget->start();
        RenderTarget::clear();
    }

    skyBox.render(camera);

    for (auto & data : renderData) {
        if (data.getType() == FORWARD) {
            data.getRenderer()->render(camera, ambient, sun, data.getData());
        }
    }

    return forwardTarget;
}
