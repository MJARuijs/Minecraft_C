#pragma once

#include <vector>
#include "Character.h"

class Word {

private:
    float fontSize;
    std::vector<Character> characters;

public:
    explicit Word(float fontSize, std::vector<Character> characters = std::vector<Character>());

    std::vector<Character> getCharacters() const;
    float getWidth();

    void operator+=(const Character & character);

};