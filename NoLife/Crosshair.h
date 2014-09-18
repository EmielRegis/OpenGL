#pragma once
#include "Drawable.h"
#include "DrawableObject2D.h"

class Crosshair :
	public Drawable
{
public:
	Crosshair();
	~Crosshair();
	virtual void draw();

private:
	DrawableObject2D *crossA;
	DrawableObject2D *crossB;
	DrawableObject2D *crossC;
	DrawableObject2D *crossD;
};

