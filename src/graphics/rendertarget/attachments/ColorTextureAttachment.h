#pragma once

#include "Attachment.h"
#include "../../textures/ColorMap.h"

class ColorTextureAttachment : public Attachment {

private:
    int index;
    bool multiSampled;
    ColorMap colorMap;

public:
    ColorTextureAttachment(int index, int width, int height, bool multiSampled);

    void init() override;

    [[nodiscard]] int getIndex() const;
    [[nodiscard]] const ColorMap &getColorMap() const;

    Attachment::Type getType() override;

    void resize(int width, int height) override;
};