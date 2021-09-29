#include "AnimatedEntity.h"

#include <utility>

AnimatedEntity::AnimatedEntity(AnimatedModel * model, Mat4 transformation) : Entity(ANIMATED, model, std::move(transformation)) {
    reinterpret_cast<AnimatedModel*>(this->model)->translateTo(this->transformation);
}

AnimatedEntity::AnimatedEntity(AnimatedModel * model) : Entity(ANIMATED, model) {}

void AnimatedEntity::render(ShaderProgram &shaderProgram) {
    reinterpret_cast<AnimatedModel*>(model)->render(shaderProgram);
}

void AnimatedEntity::update(float delta) {
    reinterpret_cast<AnimatedModel*>(model)->update(delta, transformation);
}

void AnimatedEntity::animate(const std::string& name) const {
    reinterpret_cast<AnimatedModel*>(model)->animate(name);
}

void AnimatedEntity::toggleAnimation() const {
    reinterpret_cast<AnimatedModel*>(model)->toggleAnimation();
}

void AnimatedEntity::stopAnimation() const {
    reinterpret_cast<AnimatedModel*>(model)->stopAnimation();
}

void AnimatedEntity::stopAnimating(int transitionDuration) const {
    reinterpret_cast<AnimatedModel*>(model)->stopAnimating(transitionDuration);
}
