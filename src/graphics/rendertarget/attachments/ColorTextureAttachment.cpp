#include "ColorTextureAttachment.h"

ColorTextureAttachment::ColorTextureAttachment(int index, int width, int height, bool multiSampled) : Attachment(), multiSampled(multiSampled), index(index), colorMap(width, height, multiSampled) {
    colorMap.init();
    if (multiSampled) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D_MULTISAMPLE, colorMap.getHandle(), 0);
    } else {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, colorMap.getHandle(), 0);
    }
}

void ColorTextureAttachment::init() {
    colorMap.init();
    if (multiSampled) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D_MULTISAMPLE, colorMap.getHandle(), 0);
    } else {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, colorMap.getHandle(), 0);
    }
}

Attachment::Type ColorTextureAttachment::getType() {
    return Attachment::COLOR_TEXTURE;
}

void ColorTextureAttachment::resize(int width, int height) {

}

int ColorTextureAttachment::getIndex() const {
    return index;
}

const ColorMap &ColorTextureAttachment::getColorMap() const {
    return colorMap;
}

