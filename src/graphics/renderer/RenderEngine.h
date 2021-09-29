#pragma once

#include "ForwardRenderEngine.h"
#include "DeferredRenderEngine.h"
#include "../samplers/Sampler.h"

class RenderEngine {

private:
    ForwardRenderEngine forwardEngine;
    DeferredRenderEngine deferredEngine;
    bool multiSampled;

public:
    explicit RenderEngine(bool multiSampled);

    void render(Camera & camera, AmbientLight & ambient, Sun & sun, Skybox & skybox, const std::vector<RenderData> & renderData);
};