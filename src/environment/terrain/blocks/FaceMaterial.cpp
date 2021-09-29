#include "FaceMaterial.h"

#include <utility>

FaceMaterial::FaceMaterial(std::string texturePath, Face::FaceDirection side) : texturePath(std::move(texturePath)), side(new Face::FaceDirection(side)) {}

FaceMaterial::FaceMaterial(std::string texturePath) : texturePath(std::move(texturePath)), side(nullptr) {}

const std::string &FaceMaterial::getTexturePath() const {
    return texturePath;
}

Face::FaceDirection *FaceMaterial::getSide() const {
    return side;
}
