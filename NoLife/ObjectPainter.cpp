#include "ObjectPainter.h"


ObjectPainter::ObjectPainter()
{
}


ObjectPainter::~ObjectPainter()
{
}

void ObjectPainter::paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera)
{
	scene->matV = glm::lookAt(glm::vec3(camera->getXPosition(), camera->getZPosition(), camera->getYPosition()),
		glm::vec3(camera->getXLookAtPosition(), camera->getZLookAtPosition(), camera->getYLookAtPosition()),
		glm::vec3(0.0f, 1.0f, 0.0f));
	scene->matP = glm::perspective(camera->getAngle(), (float)window->getWindowWidth() / (float)window->getWindowHeight(), 1.0f, 200.0f);

	for (Drawable* drawable : *drawables)
	{
		drawable->draw(scene);
	}
}

void ObjectPainter::paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera)
{
	scene->matV = glm::lookAt(glm::vec3(camera->getXPosition(), camera->getZPosition(), camera->getYPosition()),
		glm::vec3(camera->getXLookAtPosition(), camera->getZLookAtPosition(), camera->getYLookAtPosition()),
		glm::vec3(0.0f, 1.0f, 0.0f));
	scene->matP = glm::perspective(camera->getAngle(), (float)window->getWindowWidth() / (float)window->getWindowHeight(), 1.0f, 200.0f);

	drawable->draw(scene);
}
