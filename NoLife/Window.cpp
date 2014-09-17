#include "Window.h"


Window::Window()
{
	xPositon = 100;
	yPosition = 100;
	width = 860;
	height = 484;
	name = "New Window";
}

Window::Window(int xPosition, int yPosition, int width, int height, string name)
{
	this->xPositon = xPosition;
	this->yPosition = yPosition;
	this->width = width;
	this->height = height;
	this->name = name;
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
	//Ustawienie wymiarow przestrzeni okna
	if (height > width * 10 / 16)
	{
		this->width = width;
		this->height = width * 10 / 16;
	}
	else if (width > height * 22 / 10)
	{
		this->width = height * 22 / 10;
		this->height = height;
	}
	else
	{
		this->width = width;
		this->height = height;
	}

	OpenGLHelper::changeOpenGLWindowDimensions(this->width, this->height);
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

std::string Window::getWindowName()
{
	return this->name;
}

void Window::setWindowName(string name)
{
	this->name = name;
}


