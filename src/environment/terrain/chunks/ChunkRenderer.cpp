#include "ChunkRenderer.h"
#include "../FaceTextures.h"

ChunkRenderer::ChunkRenderer() :
        shaderProgram("res/shaders/environment/terrain/chunk.vert", "res/shaders/environment/terrain/chunk.geom", "res/shaders/environment/terrain/chunkForwardRendering.frag"),
        blockSampler(0), normalSampler(1), specularSampler(2) {}

void ChunkRenderer::render(Camera &camera, AmbientLight &ambient, Sun &sun, const std::vector<Renderable*> & chunks) {
    blockSampler.bind(FaceTextures::colorMapTexture);
    normalSampler.bind(FaceTextures::normalMapTexture);
    specularSampler.bind(FaceTextures::specularMapTexture);

    shaderProgram.start();
    shaderProgram.set("projection", camera.projectionMatrix);
    shaderProgram.set("view", camera.viewMatrix());
    shaderProgram.set("textureMap", blockSampler.index);
    shaderProgram.set("normalMap", normalSampler.index);
    shaderProgram.set("specularMap", specularSampler.index);
    shaderProgram.set("cameraPosition", camera.getPosition());

    ambient.apply(shaderProgram);
    sun.apply(shaderProgram);

    for (auto & chunk : chunks) {
        reinterpret_cast<Chunk*>(chunk)->render(shaderProgram);
    }

    ShaderProgram::stop();
}
