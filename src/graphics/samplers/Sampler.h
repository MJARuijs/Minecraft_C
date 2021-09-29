#pragma once

#include <GL/glew.h>
#include <iostream>
#include "SampleFilter.h"
#include "ClampMode.h"
#include "../textures/ImageMap.h"
#include "../textures/TextureArray.h"
#include "../textures/ColorMap.h"

class Sampler {

private:
    SampleFilter magnification;
    SampleFilter minification;
    ClampMode clamping;
    bool mipmapping;

public:
    int index;

    Sampler(int index, SampleFilter magnification, SampleFilter minification, ClampMode clamping, bool mipmapping);
    explicit Sampler(int index);

    void bind(const ColorMap& colorMap) const;
    void bind(ImageMap * imageMap) const;
    void bind(TextureArray * textureArray) const;
    void setMagnification(SampleFilter & mag);
    void setMinification(SampleFilter & min);
    void setClampMode(ClampMode & clamping);
    void setMipmapping(bool mipmap);

};
