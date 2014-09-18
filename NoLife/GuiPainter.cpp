#include "GuiPainter.h"


GuiPainter::GuiPainter()
{
}


GuiPainter::~GuiPainter()
{
}

void GuiPainter::paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera)
{
	scene->matP = glm::mat4((float)window->getWindowHeight() / window->getWindowWidth(), 0.0f, 0.0f, 0.0f, 0.0f,
		(float)window->getWindowHeight() / window->getWindowHeight(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	drawable->draw();
}

void GuiPainter::paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera)
{
	scene->matP = glm::mat4((float)window->getWindowHeight() / window->getWindowWidth(), 0.0f, 0.0f, 0.0f, 0.0f,
		(float)window->getWindowHeight() / window->getWindowHeight(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	for (Drawable* drawable : *drawables)
	{
		drawable->draw();
	}
}
