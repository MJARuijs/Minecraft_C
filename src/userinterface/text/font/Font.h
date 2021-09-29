#pragma once

#include <vector>
#include "../../../graphics/textures/ImageMap.h"
#include "../MetaData.h"
#include "../line/Character.h"

class Font {

private:
    ImageMap * textureAtlas;
    std::vector<Character> characters;

public:
    Font(ImageMap * textureAtlas, std::vector<Character> & characters);

    [[nodiscard]] ImageMap * getTextureAtlas() const;

    [[nodiscard]] float getSpaceWidth() const;
    [[nodiscard]] Character getCharacter(const char & id) const;
};