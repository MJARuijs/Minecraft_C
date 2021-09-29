#pragma once

#include "../rendertarget/RenderTarget.h"
#include "RenderData.h"
#include "../../game/Camera.h"
#include "../lights/AmbientLight.h"

class DeferredRenderEngine {

private:
//    RenderTarget * geometryTarget;
    bool multiSampled;

public:
    explicit DeferredRenderEngine(bool multiSampled);

    RenderTarget * render(Camera & camera, AmbientLight & ambient, Sun & sun, const std::vector<RenderData> & renderData, RenderTarget * forwardTarget);
};