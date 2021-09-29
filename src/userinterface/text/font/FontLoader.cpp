#include <stdexcept>
#include "FontLoader.h"
#include "../../../util/FileReader.h"
#include "../../../util/StringUtils.h"

Font * FontLoader::load(const std::string &path, float aspectRatio) {
    std::string fileName;
    if (path.find(".png") != std::string::npos) {
        int startIndex = (int)path.find_last_of('/') + 1;
        int endIndex = (int)path.find_last_of('.');
        fileName = path.substr(startIndex, endIndex - startIndex);
    } else if (path.find("optimized_") != std::string::npos) {
        int startIndex = (int)path.find_last_of('_') + 1;
        int endIndex = (int)path.find_last_of('.');
        fileName = path.substr(startIndex, endIndex - startIndex);
    } else {
        throw std::runtime_error("No font files were found at the given path!");
    }

    int dashIndex = (int)path.find_last_of('/') + 1;
    std::string directory = path.substr(0, dashIndex);

    std::string fontPath = directory + "optimized_" + fileName + ".fnt";
    std::string texturePath = directory + fileName + ".png";

    std::vector<std::string> lines = FileReader::getLines(fontPath);

    std::vector<std::string> fontProperties = StringUtils::split(lines[0], " ");

    int size = std::stoi(fontProperties[0]);
    Vec4 padding = Vec4::fromString(fontProperties[1]);
    int lineHeight = std::stoi(fontProperties[2]);
    int base = std::stoi(fontProperties[3]);
    int scaleW = std::stoi(fontProperties[4]);
    int scaleH = std::stoi(fontProperties[5]);

    MetaData metaData(size, padding, lineHeight, base, scaleW, scaleH);

    std::vector<Character> characters;
    for (int i = 1; i < lines.size(); i++) {
        characters.emplace_back(Character::fromLine(lines[i], metaData, aspectRatio));
    }

    std::cout << "Creating font: " << texturePath << ", " << fontPath << std::endl;
    return new Font(new ImageMap(ImageCache::get(texturePath)), characters);
}
