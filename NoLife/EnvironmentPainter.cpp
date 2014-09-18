#include "EnvironmentPainter.h"


EnvironmentPainter::EnvironmentPainter()
{
}


EnvironmentPainter::~EnvironmentPainter()
{
}

void EnvironmentPainter::paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera)
{
	scene->matV = glm::lookAt(glm::vec3(camera->getXPosition(), camera->getZPosition(), camera->getYPosition()),
		glm::vec3(camera->getXLookAtPosition(), camera->getZLookAtPosition(), camera->getYLookAtPosition()),
		glm::vec3(0.0f, 1.0f, 0.0f));
	scene->matP = glm::perspective(camera->getAngle(), (float)window->getWindowWidth() / (float)window->getWindowHeight(), 0.0125f, 400.0f);

	drawable->draw(scene);
}

void EnvironmentPainter::paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera)
{
	scene->matV = glm::lookAt(glm::vec3(camera->getXPosition(), camera->getZPosition(), camera->getYPosition()),
		glm::vec3(camera->getXLookAtPosition(), camera->getZLookAtPosition(), camera->getYLookAtPosition()),
		glm::vec3(0.0f, 1.0f, 0.0f));
	scene->matP = glm::perspective(camera->getAngle(), (float)window->getWindowWidth() / (float)window->getWindowHeight(), 0.0125f, 400.0f);

	for (Drawable* drawable : *drawables)
	{
		drawable->draw(scene);
	}

	
}
