#pragma once

#include "../rendertarget/RenderTarget.h"
#include "../../game/Camera.h"
#include "../lights/AmbientLight.h"
#include "../lights/Sun.h"
#include "../../environment/sky/Skybox.h"
#include "RenderData.h"

class ForwardRenderEngine {

private:
    RenderTarget * forwardTarget;
    bool multiSampled;

public:
    explicit ForwardRenderEngine(bool multiSampled);
    ~ForwardRenderEngine();

    RenderTarget * prepare();
    RenderTarget * render(Camera & camera, AmbientLight & ambient, Sun & sun, Skybox & skyBox, const std::vector<RenderData> & renderData, RenderTarget * geometryTarget);

};