#pragma once
#include "OpenGLHelper.h"
#include <functional>
#include <boost/signal.hpp>


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
	void addWindowResizeListener(std::function<void(int width, int height)> listener);
private:
	int xPositon, yPosition, width, height;
	string name;
	boost::signal<void(int, int)> windowResizeListeners;
	void initOpenGLWindowProperties();
};

