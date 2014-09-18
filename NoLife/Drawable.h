#pragma once
#include "Scene.h"

class Drawable
{
public:
	virtual void draw(Scene *scene) = 0;
};

