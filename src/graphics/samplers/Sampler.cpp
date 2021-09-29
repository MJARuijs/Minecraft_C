#include "Sampler.h"

Sampler::Sampler(int index, SampleFilter magnification, SampleFilter minification, ClampMode clamping, bool mipmapping):
    index(index),
    magnification(magnification),
    minification(minification),
    clamping(clamping),
    mipmapping(mipmapping) {
    setMagnification(magnification);
}

Sampler::Sampler(int index): index(index), magnification(SampleFilter::NEAREST), minification(SampleFilter::LINEAR), clamping(ClampMode::REPEAT), mipmapping(true) {
    setMagnification(magnification);
}

void Sampler::bind(ImageMap * imageMap) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, imageMap->getHandle());
    glActiveTexture(GL_TEXTURE0);
}

void Sampler::bind(TextureArray * textureArray) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray->getHandle());
    glActiveTexture(GL_TEXTURE0);
}

void Sampler::bind(const ColorMap& colorMap) const {
    glActiveTexture(GL_TEXTURE0 + index);
//    std::cout << colorMap.getHandle()<<std::endl;
    glBindTexture(GL_TEXTURE_2D, colorMap.getHandle());
    glActiveTexture(GL_TEXTURE0);
}

void Sampler::setMagnification(SampleFilter &mag) {
    this->magnification = mag;
    glSamplerParameteri(index, GL_TEXTURE_MAG_FILTER, mag);
}

void Sampler::setMinification(SampleFilter &min) {
    this->minification = min;
    if (mipmapping) {
        if (min == LINEAR) {
            glSamplerParameteri(index, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else if (min == NEAREST) {
            glSamplerParameteri(index, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        }
    } else {
        glSamplerParameteri(index, GL_TEXTURE_MIN_FILTER, min);
    }
}

void Sampler::setClampMode(ClampMode & clamping) {
    this->clamping = clamping;
    glSamplerParameteri(index, GL_TEXTURE_WRAP_S, clamping);
    glSamplerParameteri(index, GL_TEXTURE_WRAP_T, clamping);
    glSamplerParameteri(index, GL_TEXTURE_WRAP_R, clamping);
}

void Sampler::setMipmapping(bool mipmap) {
    this->mipmapping = mipmap;
    setMinification(this->minification);
}
