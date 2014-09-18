#pragma once
#include "Drawable.h"
#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include <vector>
class Painter
{
public:
	virtual void paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera) = 0;
	virtual void paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera) = 0;
};
