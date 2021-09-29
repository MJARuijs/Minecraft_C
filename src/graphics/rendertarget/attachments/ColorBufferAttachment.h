#pragma once

#include <GL/glew.h>
#include "Attachment.h"

class ColorBufferAttachment : public Attachment {

private:
    int index;
    int width;
    int height;
    bool multiSampled;
    GLuint handle;

public:
    ColorBufferAttachment(int index, int width, int height, bool multiSampled);

    void init() override;

    Attachment::Type getType() override;
    void resize(int width, int height) override;
};