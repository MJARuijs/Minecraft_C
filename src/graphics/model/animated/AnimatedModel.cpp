#include "AnimatedModel.h"

#include <utility>

AnimatedModel::AnimatedModel(std::vector<Shape*> shapes, Joint &rootJoint, std::vector<Pose> poses) : StaticModel(std::move(shapes)), rootJoint(rootJoint), poses(std::move(poses)), animator(rootJoint) {}

void AnimatedModel::render(ShaderProgram &shaderProgram) {
    rootJoint.loadTransformation(shaderProgram);
    StaticModel::render(shaderProgram);
}

void AnimatedModel::update(float delta, Mat4 transformation) {
    animator.update(delta, std::move(transformation));
}

void AnimatedModel::translateTo(Mat4 transformation) {
    rootJoint.initWorldTransformation(std::move(transformation));
}

std::vector<Joint> AnimatedModel::getJoints() {
    return rootJoint.getJoints();
}

void AnimatedModel::animate(const std::string &name) {
    for (auto & animation : animations) {
        if (animation.getName() == name) {
            animator.startAnimation(&animation);
            return;
        }
    }
    std::cout << "No animation with name " + name + " was found for this model..";
}

AnimatedModel & AnimatedModel::addAnimation(std::string name, const std::vector<std::pair<int, int>>& keyFrames, LoopEffect loopEffect) {
    std::vector<KeyFrame> frames;
    float totalTime = 0.0f;
    for (auto & pose : keyFrames) {
        frames.emplace_back(KeyFrame(totalTime + pose.second, poses[pose.first]));
        totalTime += pose.second;
    }
    animations.emplace_back(Animation(std::move(name), frames, loopEffect));
    return *this;
}

AnimatedModel &AnimatedModel::addAnimation(const std::string& name, const std::vector<std::pair<int, int>>& keyFrames) {
    return addAnimation(name, keyFrames, LoopEffect::NONE);
}

void AnimatedModel::toggleAnimation() {
    animator.toggleAnimation();
}

void AnimatedModel::stopAnimation() {
    animator.stopAnimation();
}

void AnimatedModel::stopAnimating(int transitionDuration) {
    animator.stopAnimating(transitionDuration);
}
