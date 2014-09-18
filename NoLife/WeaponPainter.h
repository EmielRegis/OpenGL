#pragma once
#include "Drawable.h"
#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Painter.h"

class WeaponPainter :
	public Painter
{
public:
	void paintObject(Drawable *drawable, Window *window, Scene *scene, Camera *camera);
	void paintObjects(std::vector<Drawable*> *drawables, Window *window, Scene *scene, Camera *camera);
	WeaponPainter();
	~WeaponPainter();
};

