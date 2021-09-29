#include "TexturedBackground.h"
#include "../../../resources/images/ImageCache.h"

TexturedBackground::TexturedBackground(ImageMap* textureMap, float cornerRadius, float outline,
                                       const Color& outlineColor,
                                       Color *overlayColor, Color *backgroundColor) : Background(cornerRadius, outline, outlineColor),
                                                                                      textureMap(textureMap),
                                                                                      sampler(0, NEAREST, LINEAR,REPEAT, false),
                                                                                      backgroundColor(backgroundColor),
                                                                                      overlayColor(overlayColor) {}

TexturedBackground::TexturedBackground(const std::string &path, float cornerRadius, float outline, const Color& outlineColor,
                                       Color *overlayColor, Color *backgroundColor) : Background(cornerRadius, outline, outlineColor),
                                                                                       textureMap(new ImageMap(ImageCache::get(path))),
                                                                                       sampler(0, NEAREST, LINEAR,REPEAT, false),
                                                                                       backgroundColor(backgroundColor),
                                                                                       overlayColor(overlayColor) {}

TexturedBackground::TexturedBackground(TexturedBackground * background) : Background(background->cornerRadius, background->outline, background->outlineColor), textureMap(background->textureMap),
                                                                          sampler(background->sampler),
                                                                          backgroundColor(background->backgroundColor),
                                                                          overlayColor(background->overlayColor) {}

BackgroundType TexturedBackground::getType() {
    return TEXTURED;
}

void TexturedBackground::setProperties(ShaderProgram &shaderProgram) {
    Background::setProperties(shaderProgram);
    if (backgroundColor) {
        shaderProgram.set("color", *backgroundColor);
        shaderProgram.set("hasBackground", true);
    } else {
        shaderProgram.set("hasBackground", false);
    }

    if (overlayColor) {
        shaderProgram.set("hasOverlay", true);
        shaderProgram.set("overlayColor", *overlayColor);
    } else {
        shaderProgram.set("hasOverlay", false);
    }

    shaderProgram.set("textured", true);
    shaderProgram.set("sampler", sampler.index);
    sampler.bind(textureMap);
}
