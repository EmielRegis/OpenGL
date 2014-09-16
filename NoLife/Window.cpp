#include "Window.h"


Window::Window()
{
	xPositon = 100;
	yPosition = 100;
	width = 860;
	height = 484;
}

Window::Window(int xPosition, int yPosition, int width, int height)
{
	this->xPositon = xPosition;
	this->yPosition = yPosition;
	this->width = width;
	this->height = height;
}


Window::~Window()
{
}

void Window::setPosition(int xPosition, int yPosition)
{
	this->xPositon = xPosition;
	this->yPosition = yPosition;
}

void Window::setWindowDimensions(int width, int height)
{
	this->width = width;
	this->height = height;
}

int Window::getXPosition()
{
	return xPositon;
}

int Window::getYPosition()
{
	return yPosition;
}

int Window::getWindowWidth()
{
	return width;
}

int Window::getWindowHeight()
{
	return height;
}


