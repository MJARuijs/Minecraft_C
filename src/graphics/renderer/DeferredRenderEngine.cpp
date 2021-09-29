#include "DeferredRenderEngine.h"
#include "../rendertarget/RenderTargetManager.h"

DeferredRenderEngine::DeferredRenderEngine(bool multiSampled) : multiSampled(multiSampled) {}
//, geometryTarget(nullptr)

RenderTarget* DeferredRenderEngine::render(Camera &camera, AmbientLight &ambient, Sun &sun, const std::vector<RenderData> &renderData,
                             RenderTarget * forwardTarget) {

//    geometryTarget = &RenderTargetManager::getAvailableTarget(multiSampled, 6, 0, 1, 0);

    bool containsDeferredItems = false;
    for (auto & data : renderData) {
        if (data.getType() == DEFERRED) {
            containsDeferredItems = true;
            break;
        }
    }

    if (!containsDeferredItems) {
//        return geometryTarget;
    }
    return nullptr;
}
