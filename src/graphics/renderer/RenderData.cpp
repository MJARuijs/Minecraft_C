#include "RenderData.h"

const std::vector<Renderable*> &RenderData::getData() const {
    return data;
}

Renderer *RenderData::getRenderer() const {
    return renderer;
}

RenderType RenderData::getType() const {
    return type;
}

RenderData::RenderData(std::vector<Renderable *> & data, Renderer * renderer, RenderType type) : data(data), renderer(renderer), type(type) {}
