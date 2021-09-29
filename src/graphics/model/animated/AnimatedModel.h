#pragma once

#include <vector>
#include "../Shape.h"
#include "Joint.h"
#include "animation/Pose.h"
#include "animation/Animator.h"

class AnimatedModel : public StaticModel {

private:
    std::vector<Shape *> shapes;
    std::vector<Pose> poses;
    Joint rootJoint;
    Animator animator;
    std::vector<Animation> animations;

public:
    AnimatedModel(std::vector<Shape*> shapes, Joint & rootJoint, std::vector<Pose> poses);

    void render(ShaderProgram & shaderProgram) override;
    void update(float delta, Mat4 transformation);

    AnimatedModel & addAnimation(std::string name, const std::vector<std::pair<int, int>>& keyFrames, LoopEffect loopEffect);
    AnimatedModel & addAnimation(const std::string& name, const std::vector<std::pair<int, int>>& keyFrames);

    void animate(const std::string & name);
    void toggleAnimation();
    void stopAnimation();
    void stopAnimating(int transitionDuration);
    void translateTo(Mat4 transformation);


    std::vector<Joint> getJoints();

};