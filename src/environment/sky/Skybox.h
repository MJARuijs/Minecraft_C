#pragma once

#include "../../graphics/shaders/ShaderProgram.h"
#include "../../graphics/model/static/StaticModel.h"
#include "../../game/Camera.h"
#include "../../resources/images/ImageData.h"

class Skybox {

private:
    ShaderProgram shaderProgram;
    Mesh * box;
    std::vector<ImageData*> textureData;

    float distance;
    GLuint handle;

public:
    Skybox(const std::string & path, float cameraFarPlane);
    ~Skybox();

    void render(Camera & camera);

};