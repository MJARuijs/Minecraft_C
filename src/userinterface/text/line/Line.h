#pragma once

#include <vector>
#include "Word.h"

class Line {

private:
    float maxLineWidth;
    std::vector<Word> words;

public:
    explicit Line(float maxLineWidth, std::vector<Word> words = std::vector<Word>());
    Line(float maxLineWidth, Word & word);

    [[nodiscard]] const std::vector<Word> &getWords() const;

    bool addWord(Word & newWord, float spaceWidth);

};