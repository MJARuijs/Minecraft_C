#pragma once
#include "../UniversalParameters.h"

#include "Item.h"

class ProgressBar : public Item {

private:
    float progress;
    Color progressBarColor;
    Color progressBarPausedColor;
    Color progressBarCompletedColor;

    bool paused;
    bool completed;

    Item * progressItem;

public:
    ProgressBar(std::string id, ConstraintSet & constraints, Background * background = UniversalParameters::progressBarBackground(), Color progressBarColor = UniversalParameters::progressBarColor(), Color progressBarPausedColor = UniversalParameters::progressBarPausedColor(), Color progressBarCompletedColor = UniversalParameters::progressBarCompletedColor());

    void setProgress(float newProgress);
    [[nodiscard]] float getProgress() const;

    [[nodiscard]] bool isPaused() const;

    void pause();
    void resume();

    void position(const Vec2 & parentTranslation, const Vec2 & parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> & siblingData) override;

    void draw(ShaderProgram & shaderProgram, ShaderProgram & textProgram, bool allowedToOverdraw) override;
};