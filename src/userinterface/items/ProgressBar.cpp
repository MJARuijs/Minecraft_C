#include "ProgressBar.h"
#include "../layout/constraints/constrainttypes/CenterConstraint.h"
#include "../layout/constraints/constrainttypes/PixelConstraint.h"
#include "../layout/constraints/constrainttypes/RelativeConstraint.h"

ProgressBar::ProgressBar(std::string id, ConstraintSet & constraints, Background *background, Color progressBarColor,Color progressBarPausedColor, Color progressBarCompletedColor) : Item(std::move(id), constraints, background), progressBarColor(progressBarColor), progressBarPausedColor(progressBarPausedColor), progressBarCompletedColor(progressBarCompletedColor), progress(0.0f), completed(false), paused(false), progressItem(nullptr) {
    ConstraintSet progressConstraints(
        new CenterConstraint(VERTICAL),
        new PixelConstraint(TO_LEFT),
        new RelativeConstraint(VERTICAL, 1.0f),
        new RelativeConstraint(HORIZONTAL, progress)
    );

    progressItem = new Item(id.append("_progress_bar"), progressConstraints, new ColoredBackground(progressBarColor, background->getCornerRadius()));
}

void ProgressBar::setProgress(float newProgress) {
    progress = newProgress;
    if (progress >= 1.0f) {
        progress = 1.0f;
    }
    if (progress < 0.0f) {
        progress = 0.0f;
    }

    std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> childData;
    for (auto & child : children) {
        childData.emplace_back(std::pair<std::string, std::pair<Vec2, Vec2>>(child->getId(), std::pair<Vec2, Vec2>(child->getTranslation(), child->getScale())));
    }

    progressItem->updateConstraint(RELATIVE, HORIZONTAL, progress);
    progressItem->position(getTranslation(), getScale(), childData);

    if (!completed && progress == 1.0f) {
        completed = true;
        dynamic_cast<ColoredBackground*>(progressItem->getBackground())->setColor(progressBarCompletedColor);
    }
    if (completed && progress < 1.0f) {
        completed = false;
        dynamic_cast<ColoredBackground*>(progressItem->getBackground())->setColor(progressBarColor);
    }
}

void ProgressBar::draw(ShaderProgram &shaderProgram, ShaderProgram & textProgram, bool allowedToOverdraw) {
    Item::draw(shaderProgram, textProgram, allowedToOverdraw);
    if (progressItem) {
        progressItem->draw(shaderProgram, textProgram, false);
    }
}

float ProgressBar::getProgress() const {
    return progress;
}

bool ProgressBar::isPaused() const {
    return paused;
}

void ProgressBar::pause() {
    if (!completed) {
        paused = true;
        dynamic_cast<ColoredBackground*>(progressItem->getBackground())->setColor(progressBarPausedColor);
    }
}

void ProgressBar::resume() {
    if (!completed) {
        paused = false;
        dynamic_cast<ColoredBackground*>(progressItem->getBackground())->setColor(progressBarColor);
    }
}

void ProgressBar::position(const Vec2 &parentTranslation, const Vec2 &parentScale, const std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>> &siblingData) {
    Item::position(parentTranslation, parentScale, siblingData);

    progressItem->position(getTranslation(), getScale(), siblingData);
}
