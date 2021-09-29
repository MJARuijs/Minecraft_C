#include <string>
#include "../../graphics/textures/ImageMap.h"

class ImageLoader {

public:
    ImageLoader() = default;
    ~ImageLoader() = default;

    static ImageData * load(const std::string & path);

};