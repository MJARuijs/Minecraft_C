#include "Word.h"

#include <utility>

Word::Word(float fontSize, std::vector<Character> characters) : fontSize(fontSize), characters(std::move(characters)) {}

std::vector<Character> Word::getCharacters() const {
    return characters;
}

float Word::getWidth() {
    float width = 0.0f;

    for (auto & character : characters) {
        width += character.getWidth();
    }

    return width;
}

void Word::operator+=(const Character &character) {
    characters.emplace_back(character);
}
