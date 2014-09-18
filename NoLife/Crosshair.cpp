#include "Crosshair.h"


Crosshair::Crosshair()
{
	crossA = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossA->instantScaleNatural(0.3);
	crossA->instantScale(1.0, 0.1);
	crossA->instantMove(0.0, 0.05);

	crossB = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossB->instantRotate(90);
	crossB->instantScaleNatural(0.3);
	crossB->instantScale(0.1, 1.0);
	crossB->instantMove(-0.05, 0.0);

	crossC = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossC->instantRotate(180);
	crossC->instantScaleNatural(0.3);
	crossC->instantScale(1.0, 0.1);
	crossC->instantMove(0.0, -0.05);

	crossD = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossD->instantRotate(270);
	crossD->instantScaleNatural(0.3);
	crossD->instantScale(0.1, 1.0);
	crossD->instantMove(0.05, 0.0);
}


Crosshair::~Crosshair()
{
}

void Crosshair::draw(Scene *scene)
{
	crossA->draw(scene);
	crossB->draw(scene);
	crossC->draw(scene);
	crossD->draw(scene);
}
