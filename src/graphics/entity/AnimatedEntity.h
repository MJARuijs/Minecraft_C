#pragma once

#include "Entity.h"
#include "../model/animated/AnimatedModel.h"

class AnimatedEntity : public Entity {

public:
    AnimatedEntity(AnimatedModel * model, Mat4 transformation);
    explicit AnimatedEntity(AnimatedModel * model);

    void render(ShaderProgram & shaderProgram) override;
    void update(float delta);

    void animate(const std::string& name) const;
    void toggleAnimation() const;
    void stopAnimation() const;
    void stopAnimating(int transitionDuration) const;
};