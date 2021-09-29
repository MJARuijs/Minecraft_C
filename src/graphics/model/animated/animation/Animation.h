#pragma once

#include <string>
#include <functional>
#include "KeyFrame.h"
#include "LoopEffect.h"

class Animation {

private:
    std::string name;
    std::vector<KeyFrame> keyFrames;
    LoopEffect loopEffect;
    std::function<void()> onFinish;

public:
    Animation(std::string  name, std::vector<KeyFrame> keyFrames, LoopEffect loopEffect, std::function<void()> onFinish);
    Animation(std::string name, std::vector<KeyFrame> keyFrames, std::function<void()> onFinish);
    Animation(std::string name, const std::vector<KeyFrame> & keyFrames, LoopEffect loopEffect);
    Animation(std::string name, std::vector<KeyFrame> keyFrames);

    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] std::vector<KeyFrame> getKeyFrames();
    [[nodiscard]] LoopEffect getLoopEffect() const;
    [[nodiscard]] const std::function<void()> &getOnFinish() const;

    void operator+=(const KeyFrame& keyFrame);

    int numberOfFrames();
    void executeOnFinish();

};