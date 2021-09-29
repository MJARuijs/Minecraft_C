#include "Animator.h"

#include <utility>

Animator::Animator(Joint  rootJoint) : rootJoint(std::move(rootJoint)), currentAnimation(nullptr), animationCopy(nullptr),
                                        previousFrame(), nextFrame(), currentFrameIndex(0),
                                        animationTime(0.0f), reversing(false), paused(false) {

    defaultPose = getDefaultPose();
    currentPose = getDefaultPose();
}

Animator::~Animator() {
    delete currentAnimation;
    delete animationCopy;
}

std::map<std::string, JointTransformation> Animator::getDefaultPose() {
    std::vector<Joint> defaultTransformations = rootJoint.getJoints();
    std::map<std::string, JointTransformation> defaultPose;

    for (auto & jointTransformation : defaultTransformations) {
        Mat4 defaultTransformation = jointTransformation.getDefaultTransformation();
        Vec3 position = defaultTransformation.getPosition();
        Quaternion rotation = defaultTransformation.toQuaternion();
        Vec3 scale = defaultTransformation.getScale();
        defaultPose[jointTransformation.getName()] = JointTransformation(position, rotation, scale);
    }

    return defaultPose;
}

void Animator::update(float delta, Mat4 transformation) {
    if (currentAnimation == nullptr || paused) {
        return;
    }

    updateTimer(delta);
    updateFrames();

    if (currentAnimation == nullptr) {
        return;
    }

    auto pose = calculateCurrentPose();
    applyPoseToJoints(pose, rootJoint, transformation);
}

void Animator::startAnimation(Animation * animation) {
    reset();
    currentAnimation = new Animation(animation->getName(), animation->getKeyFrames(), animation->getLoopEffect(), animation->getOnFinish());

    if (animation->numberOfFrames() == 1) {
        previousFrame = KeyFrame(0, defaultPose);
        nextFrame = animation->getKeyFrames()[0];
    } else if (animation->getKeyFrames()[0].getTimeStamp() == 0.0f) {
        previousFrame = animation->getKeyFrames()[currentFrameIndex++];
        nextFrame = animation->getKeyFrames()[currentFrameIndex++];
    } else {
        float startOffset = animation->getKeyFrames()[0].getTimeStamp();

        animationCopy = new Animation(animation->getName(), std::vector<KeyFrame>(), animation->getLoopEffect(), animation->getOnFinish());

        for (auto & keyFrame : animation->getKeyFrames()) {
            animationCopy->operator+=(KeyFrame(keyFrame.getTimeStamp() - startOffset, keyFrame.getPose()));
        }

        Animation transitionAnimation("transition_to_" + animation->getName(), { KeyFrame(0, defaultPose), animation->getKeyFrames()[0] }, LoopEffect::NONE, [&]() {
            startAnimation(animationCopy);
        });

        startAnimation(&transitionAnimation);
    }
}

void Animator::toggleAnimation() {
    paused = !paused;
}

void Animator::stopAnimating(int transitionDuration) {
    previousFrame = KeyFrame(0, currentPose);
    nextFrame = KeyFrame((float)transitionDuration, defaultPose);
    currentAnimation = new Animation("stop_animating", { previousFrame, nextFrame });
    reset();
}

void Animator::stopAnimation() {
    currentAnimation = nullptr;
    reset();
}

void Animator::reset() {
    animationTime = 0.0f;
    currentFrameIndex = 0;
    reversing = false;
}

void Animator::updateTimer(float delta) {
    if (reversing) {
        animationTime -= delta * 1000;
    } else {
        animationTime += delta * 1000;
    }
}

void Animator::updateFrames() {
    if (reversing) {
        if (animationTime < nextFrame.getTimeStamp()) {
            if (currentFrameIndex <= 0) {
                if (currentAnimation->getLoopEffect() == LoopEffect::NONE) {
                    currentAnimation->executeOnFinish();
                } else if (currentAnimation->getLoopEffect() == START_OVER) {

                } else if (currentAnimation->getLoopEffect() == REVERSING) {
                    reversing = false;
                    currentFrameIndex = 0;
                    animationTime = 0.0f;

                    previousFrame = currentAnimation->getKeyFrames()[currentFrameIndex++];
                    nextFrame = currentAnimation->getKeyFrames()[currentFrameIndex++];
                }

                if (currentAnimation->getLoopEffect() == LoopEffect::NONE) {
                    currentAnimation->executeOnFinish();
                }
            } else {
                previousFrame = nextFrame;
                nextFrame = currentAnimation->getKeyFrames()[currentFrameIndex--];
            }
        }
    } else {
        if (animationTime > nextFrame.getTimeStamp()) {
            if (currentFrameIndex >= currentAnimation->numberOfFrames()) {
                if (currentAnimation->getLoopEffect() == LoopEffect::NONE) {
                    std::function<void()> onFinish = currentAnimation->getOnFinish();
                    reset();
                    currentAnimation = nullptr;
                    onFinish();
                } else if (currentAnimation->getLoopEffect() == START_OVER) {
                    currentFrameIndex = 0;
                    animationTime = 0.0f;
                } else if (currentAnimation->getLoopEffect() == REVERSING) {
                    reversing = true;
                    currentFrameIndex = currentAnimation->numberOfFrames() - 1;
                    animationTime = nextFrame.getTimeStamp();

                    previousFrame = currentAnimation->getKeyFrames()[currentFrameIndex--];
                    nextFrame = currentAnimation->getKeyFrames()[currentFrameIndex--];
                }
            } else {
                previousFrame = nextFrame;
                nextFrame = currentAnimation->getKeyFrames()[currentFrameIndex++];
            }
        }
    }
}

std::map<std::string, JointTransformation> Animator::calculateCurrentPose() {
    float progression = calculateProgression(previousFrame.getTimeStamp(), nextFrame.getTimeStamp());
    return interpolatePoses(previousFrame, nextFrame, progression);
}

void Animator::applyPoseToJoints(std::map<std::string, JointTransformation> currentPose, Joint & joint, Mat4 & parentTransformation) {
    JointTransformation currentLocalTransformation = currentPose[joint.getName()];
    Mat4 currentWorldTransformation = parentTransformation * currentLocalTransformation.getTransformationMatrix();

    joint.calculateAnimatedTransformation(currentWorldTransformation);

    for (auto & child : joint.getChildren()) {
        applyPoseToJoints(currentPose, *child, currentWorldTransformation);
    }
}

float Animator::calculateProgression(float previousFrameTime, float nextFrameTime) const {
    float totalTime = nextFrameTime - previousFrameTime;
    float currentTime = animationTime - previousFrameTime;
    return currentTime / totalTime;
}

std::map<std::string, JointTransformation> Animator::interpolatePoses(KeyFrame & previousFrame, KeyFrame & nextFrame, float progression) {
    auto p = previousFrame.getPose().getJointTransformations();

    for (auto & it : p) {
        std::string jointName = it.first;

        JointTransformation previousTransformation = previousFrame.getPose().getJointTransformations()[jointName];
        JointTransformation nextTransformation = nextFrame.getPose().getJointTransformations()[jointName];
        JointTransformation currentTransformation = JointTransformation::interpolate(previousTransformation, nextTransformation, progression);
        currentPose[jointName] = currentTransformation;
    }

    return currentPose;
}
