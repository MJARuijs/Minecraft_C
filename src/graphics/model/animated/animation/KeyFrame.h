#pragma once

#include "Pose.h"

class KeyFrame {

private:
    float timeStamp;
    Pose pose;

public:
    KeyFrame(float timeStamp, Pose  pose);
    KeyFrame(float timeStamp, std::map<std::string, JointTransformation> jointTransformations);
    KeyFrame();

    [[nodiscard]] float getTimeStamp() const;

    void setTimeStamp(float timeStamp);

    Pose getPose();
};