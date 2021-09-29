#pragma once

#include <string>
#include "../chunks/Face.h"

class FaceMaterial {

private:
    std::string texturePath;
    Face::FaceDirection * side;

public:
    FaceMaterial(std::string texturePath, Face::FaceDirection side);
    explicit FaceMaterial(std::string texturePath);

    [[nodiscard]] const std::string & getTexturePath() const;
    [[nodiscard]] Face::FaceDirection * getSide() const;

};