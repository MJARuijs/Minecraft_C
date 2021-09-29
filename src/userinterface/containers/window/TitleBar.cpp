#include "TitleBar.h"
#include "../../layout/constraints/constrainttypes/CenterConstraint.h"
#include "../../layout/constraints/constrainttypes/PixelConstraint.h"
#include "../../layout/constraints/constrainttypes/RelativeConstraint.h"

TitleBar::TitleBar(float height, Background * background, const Vec2 & parentTranslation, const Vec2 & parentScale) : background(background) {
    constraints += new CenterConstraint(VERTICAL);
    constraints += new PixelConstraint(TO_TOP, 0.0f);
    constraints += new RelativeConstraint(HORIZONTAL, 1.0f);
    constraints += new RelativeConstraint(VERTICAL, height);

    constraints.apply(parentTranslation, parentScale, std::vector<std::pair<std::string, std::pair<Vec2, Vec2>>>());
}

Vec2 TitleBar::getScale() const {
    return constraints.getScale();
}

void TitleBar::draw(ShaderProgram &shaderProgram) {
    shaderProgram.set("translation", constraints.getTranslation());
    shaderProgram.set("scale", constraints.getScale());
    shaderProgram.set("allowedToOverdraw", true);
    background->setProperties(shaderProgram);

    quad.draw();
}

void TitleBar::update(Mouse &mouse, float aspectRatio, float deltaTime) {

}
