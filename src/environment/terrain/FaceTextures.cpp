#include "FaceTextures.h"

TextureArray * FaceTextures::colorMapTexture = nullptr;
TextureArray * FaceTextures::normalMapTexture = nullptr;
TextureArray * FaceTextures::specularMapTexture = nullptr;

std::vector<std::pair<std::string, ImageData*>> FaceTextures::colorMaps = {};
std::vector<std::pair<std::string, ImageData*>> FaceTextures::normalMaps = {};
std::vector<std::pair<std::string, ImageData*>> FaceTextures::specularMaps = {};

void FaceTextures::load(const std::string &path) {
    DIR * colorMapsDirectory = opendir((path + "/colorMaps").c_str());

    if (colorMapsDirectory == nullptr) {
        return;
    }

    std::vector<std::string> textureFiles;

    struct dirent * entry;

    while (true) {
        entry = readdir(colorMapsDirectory);
        if (!entry) {
            break;
        }
        textureFiles.emplace_back(entry->d_name);
    }

    closedir(colorMapsDirectory);

    std::vector<ImageData*> colorMapTextures;
    std::vector<ImageData*> normalMapTextures;
    std::vector<ImageData*> specularMapTextures;

    for (auto & textureFile : textureFiles) {
        if (StringUtils::endsWith(textureFile, "mcmeta") || textureFile == "." || textureFile == "..") {
            continue;
        }
        std::string normalDirectory = StringUtils::removeSuffix(textureFile, ".png") + "_n.png";
        std::string specularDirectory = StringUtils::removeSuffix(textureFile, ".png") + "_s.png";

        ImageData * colorMap = ImageCache::get(path + std::string("/colorMaps/").append(textureFile));
        ImageData * normalMap = nullptr;
        ImageData * specularMap = nullptr;

        try {
            normalMap = ImageCache::get(path + std::string("/normalMaps/").append(normalDirectory));
        } catch (...) {

        }

        try {
            specularMap = ImageCache::get(path + std::string("/specularMaps/").append(specularDirectory));
        } catch (...) {

        }

        colorMaps.emplace_back(textureFile, colorMap);
        colorMapTextures.emplace_back(colorMap);

        if (normalMap) {
            normalMaps.emplace_back(normalDirectory, normalMap);
            normalMapTextures.emplace_back(normalMap);
        }

        if (specularMap) {
            specularMaps.emplace_back(specularDirectory, specularMap);
            specularMapTextures.emplace_back(specularMap);
        }
    }

    colorMapTexture = new TextureArray(colorMapTextures);
    normalMapTexture = new TextureArray(normalMapTextures);
    specularMapTexture = new TextureArray(specularMapTextures);
}

int FaceTextures::getTextureIndex(const std::string &path) {
    int i = 0;
    for (auto & colorMap : colorMaps) {
        if (colorMap.first == path + ".png") {
            return i;
        }
        i++;
    }
    return -1;
}

int FaceTextures::getNormalIndex(const std::string &path) {
    int i = 0;
    for (auto & normalMap : normalMaps) {
        if (normalMap.first == path + "_n.png") {
            return i;
        }
        i++;
    }
    return -1;
}

int FaceTextures::getSpecularIndex(const std::string &path) {
    int i = 0;
    for (auto & specularMap : specularMaps) {
        if (specularMap.first == path + "_s.png") {
            return i;
        }
        i++;
    }
    return -1;
}