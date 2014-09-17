#pragma once
#include "OpenGLHelper.h"

class Window
{
public:
	Window();
	Window(int xPosition, int yPosition, int width, int height, string name);
	~Window();
	int getXPosition();
	int getYPosition();
	int getWindowWidth();
	int getWindowHeight();
	string getWindowName();
	void setPosition(int xPosition, int yPosition);
	void setWindowDimensions(int width, int height);
	void setWindowName(string name);
private:
	int xPositon, yPosition, width, height;
	string name;
	void initOpenGLWindowProperties();
};

