#include "Skybox.h"
#include "../../graphics/model/static/StaticModelCache.h"
#include "../../resources/images/ImageCache.h"
#include "../../graphics/GraphicsContext.h"
#include "../../graphics/model/mesh/MeshCache.h"

Skybox::Skybox(const std::string &path, float cameraFarPlane) :
    shaderProgram("res/shaders/environment/sky/skybox.vert", "res/shaders/environment/sky/skybox.frag"),
    box(MeshCache::get("res/models/box.dae")),
    distance(sqrtf((cameraFarPlane * cameraFarPlane) / 3.0f)),
    handle(0) {

    glGenTextures(1, &handle);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

    std::string correctSide = "front";
    textureData.emplace_back(ImageCache::get(path + "/" + correctSide + ".jpg"));
    textureData.emplace_back(ImageCache::get(path + "/" + correctSide + ".jpg"));
    textureData.emplace_back(ImageCache::get(path + "/top.jpg"));
    textureData.emplace_back(ImageCache::get(path + "/bottom.jpg"));
    textureData.emplace_back(ImageCache::get(path + "/" + correctSide + ".jpg"));
    textureData.emplace_back(ImageCache::get(path + "/" + correctSide + ".jpg"));

    int i = 0;
    for (auto & texture : textureData) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->getData());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::render(Camera &camera) {
    GraphicsContext::disable(GraphicsContext::FACE_CULLING);

    shaderProgram.start();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

    shaderProgram.set("cubeMap", 0);
    shaderProgram.set("projection", camera.projectionMatrix);
    shaderProgram.set("view", camera.viewMatrix());
    shaderProgram.set("distance", distance);

    box->render();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    ShaderProgram::stop();
    GraphicsContext::enable(GraphicsContext::FACE_CULLING);
}

Skybox::~Skybox() {
    for (auto texture : textureData) {
        delete texture;
    }
}
