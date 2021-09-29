#include "Line.h"

#include <utility>

Line::Line(float maxLineWidth, std::vector<Word> words) : maxLineWidth(maxLineWidth), words(std::move(words)) {}

Line::Line(float maxLineWidth, Word & word) : maxLineWidth(maxLineWidth) {
    words.emplace_back(word);
}

bool Line::addWord(Word &newWord, float spaceWidth) {
    float currentLineWidth = 0.0f;

    for (auto & word : words) {
        currentLineWidth += word.getWidth() + spaceWidth;
    }

    if (currentLineWidth + newWord.getWidth() > maxLineWidth) {
        return false;
    }

    words.emplace_back(newWord);
    return true;
}

const std::vector<Word> &Line::getWords() const {
    return words;
}
