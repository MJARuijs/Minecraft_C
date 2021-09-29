#pragma once

#include <string>
#include "Font.h"
#include "../../../resources/images/ImageCache.h"

class FontLoader {

public:
    FontLoader() = default;
    ~FontLoader() = default;

    static Font * load(const std::string & path, float aspectRatio);

};