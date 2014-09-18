#pragma once
#include "libraries/gl/glew.h"
#include "libraries/gl/freeglut.h"
#include "libraries/glm/glm.hpp"
#include "boost/signal.hpp"
#include <functional>


enum KeyFunctionalEnum
{
	KEY_SPACE = 20,
	KEY_BACKSPACE = 8,
	KEY_SHIFT_LEFT = GLUT_KEY_SHIFT_L,
	KEY_SHIFT_RIGHT = GLUT_KEY_SHIFT_R,
	KEY_ALT_LEFT = GLUT_KEY_ALT_L,
	KEY_ALT_RIGHT = GLUT_KEY_ALT_R,
	KEY_ESCAPE = 27
};

class Keyboard
{
public:
	void keyDown(unsigned char, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void keyFunctionalDown(int key, int x, int y);
	void keyFunctionalUp(int key, int x, int y);
	void addKeyDownListener(std::function<void(unsigned char, int, int)> listener);
	void addKeyUpListener(std::function<void(unsigned char, int, int)> listener);
	void addKeyFunctionalDownListener(std::function<void(KeyFunctionalEnum, int, int)> listener);
	void addKeyFunctionalUpListener(std::function<void(KeyFunctionalEnum, int, int)> listener);
	bool isKeyActive(unsigned char key);
	bool isKeyFunctionalActive(KeyFunctionalEnum key);
	Keyboard();
	~Keyboard();

	

private:
	boost::signal<void(unsigned char, int, int)> keyDownListeners;
	boost::signal<void(unsigned char, int, int)> keyUpListeners;
	boost::signal<void(KeyFunctionalEnum, int, int)> keyFunctionalDownListeners;
	boost::signal<void(KeyFunctionalEnum, int, int)> keyFunctionalUpListeners;

	std::map<unsigned char, bool> keyMap;
	std::map<int, bool> keyFunctionalMap;
};



