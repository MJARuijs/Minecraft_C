#pragma once

#include "../../../graphics/shaders/ShaderProgram.h"
#include "../../../game/Camera.h"
#include "../../../graphics/lights/Sun.h"
#include "../../../graphics/lights/AmbientLight.h"
#include "Chunk.h"
#include "../../../graphics/samplers/Sampler.h"
#include "../../../graphics/renderer/Renderer.h"

class ChunkRenderer : public Renderer {

private:
    ShaderProgram shaderProgram;
    Sampler blockSampler;
    Sampler normalSampler;
    Sampler specularSampler;

public:
    ChunkRenderer();

    void render(Camera & camera, AmbientLight & ambient, Sun & sun, const std::vector<Renderable*> & chunks) override;

};