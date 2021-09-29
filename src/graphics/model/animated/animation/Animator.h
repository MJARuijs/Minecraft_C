#pragma once

#include <string>
#include <map>
#include "../JointTransformation.h"
#include "Animation.h"
#include "KeyFrame.h"
#include "../Joint.h"

class Animator {

private:
    Joint rootJoint;
    std::map<std::string, JointTransformation> currentPose;
    std::map<std::string, JointTransformation> defaultPose;

    Animation * currentAnimation;
    Animation * animationCopy;

    KeyFrame previousFrame;
    KeyFrame nextFrame;
    int currentFrameIndex;
    float animationTime;
    bool reversing;
    bool paused;

    std::map<std::string, JointTransformation> getDefaultPose();
    void reset();

    void updateTimer(float delta);
    void updateFrames();

    std::map<std::string, JointTransformation> calculateCurrentPose();
    void applyPoseToJoints(std::map<std::string, JointTransformation> currentPose, Joint & rootJoint, Mat4& parentTransformation);
    float calculateProgression(float previousFrameTime, float nextFrameTime) const;
    std::map<std::string, JointTransformation> interpolatePoses(KeyFrame & previousFrame, KeyFrame & nextFrame, float progression);

public:
    explicit Animator(Joint  rootJoint);
    ~Animator();

    void update(float delta, Mat4 transformation);
    void startAnimation(Animation * animation);
    void toggleAnimation();
    void stopAnimating(int transitionDuration);
    void stopAnimation();


};