#pragma once

#include <map>
#include "Font.h"

class FontCache {

private:
    static std::map<std::string, Font*> cache;

public:
    static Font * get(const std::string & path, float aspectRatio);
};