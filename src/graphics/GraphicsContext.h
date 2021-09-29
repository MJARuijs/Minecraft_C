#pragma once
#include <GL/glew.h>
#include "../math/Color.h"

class GraphicsContext {

public:
    enum Option {
        FACE_CULLING,
        DEPTH_TESTING,
        ALPHA_BLENDING,
        TEXTURE_MAPPING,
        MULTI_SAMPLE,
        DEPTH_BUFFER_BIT,
        COLOR_BUFFER_BIT
    };

    static void init(const Color & color);

    static void enable(Option option);
    static void disable(Option option);

    static int getCode(Option option);

};