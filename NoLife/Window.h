#pragma once
class Window
{
public:
	Window();
	Window(int xPosition, int yPosition, int width, int height);
	~Window();
	int getXPosition();
	int getYPosition();
	int getWindowWidth();
	int getWindowHeight();
	void setPosition(int xPosition, int yPosition);
	void setWindowDimensions(int width, int height);
private:
	int xPositon, yPosition, width, height;
};

