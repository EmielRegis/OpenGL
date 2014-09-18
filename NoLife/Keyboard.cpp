#include "Keyboard.h"


Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		keyMap.insert(std::pair<unsigned char, bool>((unsigned char)i, false));
	}

	keyFunctionalMap.insert(std::pair<int, bool>(KEY_BACKSPACE, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_ALT_LEFT, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_ALT_RIGHT, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_ESCAPE, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_SHIFT_LEFT, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_SHIFT_RIGHT, false));
	keyFunctionalMap.insert(std::pair<int, bool>(KEY_SPACE, false));

}


Keyboard::~Keyboard()
{
}

void Keyboard::keyFunctionalDown(int key, int x, int y)
{
	if (keyFunctionalMap.count(key) > 0)
	{
		keyFunctionalMap[key] = true;
		KeyFunctionalEnum e = (KeyFunctionalEnum)key;
		keyFunctionalDownListeners(e, x, y);
	}

	
}

void Keyboard::keyFunctionalUp(int key, int x, int y)
{
	if (keyFunctionalMap.count(key) > 0)
	{
		keyFunctionalMap[key] = false;
		KeyFunctionalEnum e = (KeyFunctionalEnum)key;
		keyFunctionalUpListeners(e, x, y);
	}
}

void Keyboard::keyDown(unsigned char key, int x, int y)
{
	if (keyMap.count(key) > 0)
	{
		keyMap[key] = true;
		keyDownListeners(key, x, y);
	}
}

void Keyboard::keyUp(unsigned char key, int x, int y)
{
	if (keyMap.count(key) > 0)
	{
		keyMap[key] = false;
		keyUpListeners(key, x, y);
	}
}

void Keyboard::addKeyDownListener(std::function<void(unsigned char, int, int)> listener)
{
	keyDownListeners.connect(listener);
}

void Keyboard::addKeyUpListener(std::function<void(unsigned char, int, int)> listener)
{
	keyUpListeners.connect(listener);
}

void Keyboard::addKeyFunctionalDownListener(std::function<void(KeyFunctionalEnum, int, int)> listener)
{
	keyFunctionalDownListeners.connect(listener);
}

void Keyboard::addKeyFunctionalUpListener(std::function<void(KeyFunctionalEnum, int, int)> listener)
{
	keyFunctionalUpListeners.connect(listener);
}

bool Keyboard::isKeyActive(unsigned char key)
{
	return keyMap[key];
}

bool Keyboard::isKeyFunctionalActive(KeyFunctionalEnum key)
{
	return keyFunctionalMap[key];
}


