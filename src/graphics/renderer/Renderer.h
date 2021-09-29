#pragma once

#include "../Quad.h"
#include "Renderable.h"
#include "../lights/Sun.h"
#include "../../game/Camera.h"
#include "../lights/AmbientLight.h"

class Renderer {

private:
    Quad quad;

public:
    virtual void render(Camera & camera, AmbientLight & ambient, Sun & sun, const std::vector<Renderable*> & items) = 0;

};