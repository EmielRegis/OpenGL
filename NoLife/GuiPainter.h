#pragma once
#include "Drawable.h"
#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Painter.h"

class GuiPainter : Painter
{
public:
	void paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera);
	void paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera);
	GuiPainter();
	~GuiPainter();
};

