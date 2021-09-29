#pragma once

#include "Renderable.h"
#include "Renderer.h"
#include "RenderType.h"

class RenderData {

private:
    std::vector<Renderable*> data;
    Renderer* renderer;
    RenderType type;

public:
    RenderData(std::vector<Renderable *> & data, Renderer * renderer, RenderType type);

    const std::vector<Renderable*> &getData() const;
    [[nodiscard]] Renderer *getRenderer() const;
    [[nodiscard]] RenderType getType() const;

};