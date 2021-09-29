#pragma once

#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>
#include "../../resources/images/ImageData.h"
#include "../../util/StringUtils.h"
#include "../../resources/images/ImageCache.h"
#include "../../graphics/textures/TextureArray.h"

class FaceTextures {

private:
    static std::vector<std::pair<std::string, ImageData*>> colorMaps;
    static std::vector<std::pair<std::string, ImageData*>> normalMaps;
    static std::vector<std::pair<std::string, ImageData*>> specularMaps;

public:

    static TextureArray* colorMapTexture;
    static TextureArray* normalMapTexture;
    static TextureArray* specularMapTexture;

    static void load(const std::string & path);

    static int getTextureIndex(const std::string & path);
    static int getNormalIndex(const std::string & path);
    static int getSpecularIndex(const std::string & path);
};