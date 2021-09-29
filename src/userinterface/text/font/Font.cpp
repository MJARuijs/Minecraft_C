#include "Font.h"

#include <stdexcept>

Font::Font(ImageMap * textureAtlas, std::vector<Character> & characters)
        : textureAtlas(textureAtlas), characters(characters) {}

float Font::getSpaceWidth() const {
    Character spaceCharacter = getCharacter(32);
    return spaceCharacter.getAdvance();
}

Character Font::getCharacter(const char & id) const {
    for (auto character : characters) {
        if (character.getId() == id) {
            return character;
        }
    }
    throw std::runtime_error("Invalid character could not be found!");
}

ImageMap * Font::getTextureAtlas() const {
    return textureAtlas;
}
