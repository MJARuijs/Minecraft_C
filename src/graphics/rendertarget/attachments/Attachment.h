#pragma once

class Attachment {

public:

    enum Type {
        COLOR_TEXTURE,
        COLOR_BUFFER,
        DEPTH_TEXTURE,
        DEPTH_BUFFER
    };

    virtual ~Attachment() = default;

    virtual void init() = 0;

    virtual void resize(int width, int height) = 0;

    virtual Type getType() = 0;

};