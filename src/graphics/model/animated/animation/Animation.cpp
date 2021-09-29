#include "Animation.h"

#include <utility>
#include <iostream>

Animation::Animation(std::string name, std::vector<KeyFrame> keyFrames) : name(std::move(name)), keyFrames(std::move(keyFrames)), loopEffect(NONE), onFinish() {}

Animation::Animation(std::string name, std::vector<KeyFrame> keyFrames, std::function<void()> onFinish) : name(std::move(name)), keyFrames(std::move(keyFrames)), loopEffect(NONE), onFinish(std::move(onFinish)) {}

Animation::Animation(std::string name, const std::vector<KeyFrame> & keyFrames, LoopEffect loopEffect) : name(std::move(name)), keyFrames(keyFrames), loopEffect(loopEffect), onFinish() {
    if (loopEffect != NONE && keyFrames.size() == 1) {
        throw std::runtime_error("Cannot create a looping animation with only 1 keyframe..");
    }
}

Animation::Animation(std::string  name, std::vector<KeyFrame> keyFrames, LoopEffect loopEffect, std::function<void()> onFinish) : name(std::move(name)), keyFrames(std::move(keyFrames)), loopEffect(loopEffect), onFinish(std::move(onFinish)) {
    if (loopEffect != NONE && keyFrames.size() == 1) {
        throw std::runtime_error("Cannot create a looping animation with only 1 keyframe..");
    }
}

void Animation::operator+=(const KeyFrame& keyFrame) {
    keyFrames.emplace_back(keyFrame);
}

int Animation::numberOfFrames() {
    return keyFrames.size();
}

const std::string &Animation::getName() const {
    return name;
}

std::vector<KeyFrame> Animation::getKeyFrames() {
    return keyFrames;
}

LoopEffect Animation::getLoopEffect() const {
    return loopEffect;
}

const std::function<void()> &Animation::getOnFinish() const {
    return onFinish;
}

void Animation::executeOnFinish() {
    onFinish();
}
