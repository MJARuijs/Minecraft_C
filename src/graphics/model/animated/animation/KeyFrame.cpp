#include "KeyFrame.h"

#include <utility>
#include <iostream>

KeyFrame::KeyFrame(float timeStamp, Pose pose) : timeStamp(timeStamp), pose(std::move(pose)) {}

KeyFrame::KeyFrame(float timeStamp, std::map<std::string, JointTransformation> jointTransformations) : timeStamp(timeStamp), pose((std::move(jointTransformations))) {}

KeyFrame::KeyFrame() : timeStamp(-1) {}

float KeyFrame::getTimeStamp() const {
    return timeStamp;
}

Pose KeyFrame::getPose() {
    return pose;
}

void KeyFrame::setTimeStamp(float timeStamp) {
    KeyFrame::timeStamp = timeStamp;
}
