#pragma once
#include "libraries/gl/glew.h"
#include "libraries/gl/freeglut.h"
#include "libraries/glm/glm.hpp"
#include "libraries/glm/gtc/matrix_transform.hpp"
#include "libraries/glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "libraries/tga/tga.h"
#include "libraries/shaderprogram/shaderprogram.h"
#include "vector"
#include <ios>
#include <sstream>
#include "Scene.h"
#include "DrawableObject.h"
#include "DrawableObject2D.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include "MusicMixer.h"
#include "Window.h"
#include "Camera.h"
#include "OpenGLHelper.h"
#include "EnvironmentPainter.h"
#include "GuiPainter.h"
#include "Painter.h"
#include "ObjectPainter.h"
#include "WeaponPainter.h"
#include "Crosshair.h"
#include "Keyboard.h"

#include "Leap.h"
#include "LeapMotionManager.h"

using namespace std;
using namespace Leap;

Window *window;
Camera *camera;
Scene &scene = Scene::getInstance();
MusicMixer *mixer;
Keyboard *keyboard;

EnvironmentPainter *environmentPainter;
Painter *simpleObjectsPainter;
WeaponPainter *weaponPainter;
GuiPainter *guiPainter;

vector<Drawable*> *environmentObjects;
vector<Drawable*> *guiObjects;
vector<Drawable*> *simpleObjects;

DrawableObject *kostka;
DrawableObject *malpa;
DrawableObject *USS;
DrawableObject *demon;
DrawableObject *floore;
DrawableObject *terrain;
DrawableObject *skydome;
DrawableObject *smallDragon;
DrawableObject *house;
DrawableObject *weapon;
DrawableObject2D *obj2D;
Crosshair *crosshair;

Controller *controller;
LeapMotionManager *leapManager;


//bool keyW = false, keyS = false, keyA = false, keyD = false, keyE = false, keyShift = false, keySpace = false, keyZ = false, keyX = false, keyC = false;
int mouseXY = 0, mouseZ;

bool shotFlag = false;
bool canShotFlag = true;
bool jumpFlag = true;

//Zmienne do animacji
float speed = 120; //120 stopni/s
int lastTime = 0;
float angle = 0;

// zmienne do poruszania sie
float stepX = 0.0f, stepY = 0.0f, stepZ = 0.0f,
i = 225,
k = 90,
j = 0;

//int normalMoveCoef = 100, speedMoveCoef = 60;
int normalMoveCoef = 400, speedMoveCoef = 240;


//Procedura rysuj¹ca
void displayFrame() {
	glClearColor(1.0, 1.0, 1.0, 0.1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	kostka->instantRotate(0, 0, angle - kostka->getZRotationAngle());
	USS->instantRotate(0, 0, angle - USS->getZRotationAngle());

	environmentPainter->paintObjects(environmentObjects, window, &scene, camera);
	simpleObjectsPainter->paintObjects(simpleObjects, window, &scene, camera);
	weaponPainter->paintObject(weapon, window, &scene, camera);
	guiPainter->paintObjects(guiObjects, window, &scene, camera);

	glutSwapBuffers();
}

void jump()
{
	jumpFlag = false;
	float obsZ = camera->getZPosition();
	for (float i = 0.0f; i < 3.14f; i += 0.1f)
	{
		
		obsZ = 2.0f + 2.0f * sin(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		camera->setPosition(camera->getXPosition(), camera->getYPosition(), obsZ);
	}
	camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f);
	jumpFlag = true;
}



void playerMoveListener()
{
	glm::vec3 look = glm::vec3(0, 0, 1);
	float lookLength = glm::sqrt(look.x*look.x + look.z*look.z + look.y*look.y);

	glm::vec3 objToCam = glm::normalize(glm::vec3(camera->getXPosition(), 0, camera->getYPosition()) - glm::vec3(demon->getXCoordinate(), 0, demon->getYCoordinate()));
	float objToCamLength = glm::sqrt(objToCam.x*objToCam.x + objToCam.z*objToCam.z + objToCam.y*objToCam.y);

	float deg = glm::degrees(acos(glm::dot(look, objToCam) / (glm::abs(lookLength) * glm::abs(objToCamLength))));

	if (camera->getXPosition() < 0) { deg = -deg; }

	demon->instantRotate(0, 0, deg - demon->getZRotationAngle());
}

// kontrola naciskania klawiszy klawiatury
void keyPressed(unsigned char key, int x, int y)
{
	float obsX = camera->getXPosition(), obsY = camera->getYPosition(), obsZ = camera->getZPosition(),
		pktX = camera->getXLookAtPosition(), pktY = camera->getYLookAtPosition(), pktZ = camera->getZLookAtPosition();

	playerMoveListener();

	if (keyboard->isKeyActive('w') || leapManager->isKeyActive(KEY_VIRTUAL_W))
	{
		if (keyboard->isKeyActive('e') || leapManager->isKeyActive(KEY_VIRTUAL_E))
		{
			j += 0.15;
			obsZ = 1.8 + sin(j) / 9;

			stepX = (pktX - obsX) / speedMoveCoef;
			stepY = (pktY - obsY) / speedMoveCoef;
		}
		else
		{
			stepX = (pktX - obsX) / normalMoveCoef;
			stepY = (pktY - obsY) / normalMoveCoef;
		}

		obsX += stepX;
		obsY += stepY;
		pktX += stepX;
		pktY += stepY;

		skydome->instantMove(stepX, stepY, 0);
	}
	if (keyboard->isKeyActive('s') || leapManager->isKeyActive(KEY_VIRTUAL_S))
	{
		if (keyboard->isKeyActive('e') || leapManager->isKeyActive(KEY_VIRTUAL_E))
		{
			j += 0.15;
			obsZ = 1.8 + sin(j) / 9;

			stepX = (pktX - obsX) / speedMoveCoef;
			stepY = (pktY - obsY) / speedMoveCoef;
		}
		else
		{
			stepX = (pktX - obsX) / normalMoveCoef;
			stepY = (pktY - obsY) / normalMoveCoef;
		}

		obsX -= stepX;
		obsY -= stepY;
		pktX -= stepX;
		pktY -= stepY;

		skydome->instantMove(-stepX, -stepY, 0);
	}
	if (keyboard->isKeyActive('a') || leapManager->isKeyActive(KEY_VIRTUAL_A))
	{
		stepX = -(pktY - obsY) / normalMoveCoef;
		stepY = (pktX - obsX) / normalMoveCoef;

		stepX *= 0.6f;
		stepY *= 0.6f;

		obsX -= stepX;
		obsY -= stepY;
		pktX -= stepX;
		pktY -= stepY;

		skydome->instantMove(-stepX, -stepY, 0);

	}
	if (keyboard->isKeyActive('d') || leapManager->isKeyActive(KEY_VIRTUAL_D))
	{
		stepX = -(pktY - obsY) / normalMoveCoef;
		stepY = (pktX - obsX) / normalMoveCoef;

		stepX *= 0.6f;
		stepY *= 0.6f;

		obsX += stepX;
		obsY += stepY;
		pktX += stepX;
		pktY += stepY;

		skydome->instantMove(stepX, stepY, 0);
	}

	camera->setPosition(obsX, obsY, obsZ);
	camera->setLookAtPoint(pktX, pktY, pktZ);

	if (leapManager->isKeyActive(KEY_VIRTUAL_Z)) { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f); }
	else if (leapManager->isKeyActive(KEY_VIRTUAL_X)) { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 1.0f); }
	else if (leapManager->isKeyActive(KEY_VIRTUAL_C)) { camera->setPosition(camera->getXPosition(), camera->getZPosition(), 0.5f); }

	if (leapManager->isKeyActive(KEY_VIRTUAL_SPACE))
	{
		if (jumpFlag)
		{	
			jumpFlag = false;
			std::thread first(jump);
			first.detach();
		}
	}


}


void keyDown(unsigned char c, int x, int y)
{
	if (c == 'z' || leapManager->isKeyActive(KEY_VIRTUAL_Z)) { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f); }
	else if (c == 'x' || leapManager->isKeyActive(KEY_VIRTUAL_X)) { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 1.0f); }
	else if (c == 'c' || leapManager->isKeyActive(KEY_VIRTUAL_C)) { camera->setPosition(camera->getXPosition(), camera->getZPosition(), 0.5f); }
}




void keyUp(unsigned char c, int x, int y)
{
	if (c == 'e')
	{
		camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f);
	}
	if (c == ' ')
	{
		if (jumpFlag)
		{
			jumpFlag = false;
			std::thread first(jump);
			first.detach();
		}
	}
	if (c == 'n') { mixer->playBackgroundMusic(); }
	if (c == 'm')
	{
		if (mixer->getBackgroundMusicVolume() < 0.02f) { mixer->enableBackgroundMusic(); }
		else { mixer->muteBackgroundMusic(); }
	}
}

void virtualMouseMove()
{
	int z = 0;
	int xy = 0;

	if (leapManager->isKeyActive(KEY_VIRTUAL_I) || leapManager->isKeyActive(KEY_VIRTUAL_O))
	{
		if (leapManager->isKeyActive(KEY_VIRTUAL_I)) xy = -1;
		else if (leapManager->isKeyActive(KEY_VIRTUAL_O)) xy = 1;

		i = (i > 0) ? i + (float)xy/1.5f : 360;
	}
	else
	{
		if (leapManager->isKeyActive(KEY_VIRTUAL_MOUSE_MOVE_LEFT)) xy = -1;
		else if (leapManager->isKeyActive(KEY_VIRTUAL_MOUSE_MOVE_RIGHT)) xy = 1;

		i = (i > 0) ? i + (float)xy/4.0f : 360;


		if (leapManager->isKeyActive(KEY_VIRTUAL_MOUSE_MOVE_UP)) z = 1;
		else if (leapManager->isKeyActive(KEY_VIRTUAL_MOUSE_MOVE_DOWN)) z = -1;

		if (k > 10)
		{
			if ((k < 180) && k >= -z && (180 - k) >= z) { k += (float)z/4.0f; }
			else if (z < 0) { k += (float)z/4.0f; }
		}
		else if (z > 0) { k += (float)z/4.0f; }
	}
	
	


	camera->rotateCamera(i, i, k);
}

void passiveMouseMove(int x, int y)
{
	int xy = x;// -windowWidth / 2;
	int z = y;// -windowHeight / 2;

	xy = xy - mouseXY;
	z = z - mouseZ;

	mouseXY = x;
	mouseZ = y;

	cout << i << endl;
	i = (i > 0) ? i + xy : 360;

	if (k > 10)
	{
		if ((k < 180) && k >= -z && (180 - k) >= z) { k += z; }
		else if (z < 0) { k += z; }
	}
	else if (z > 0) { k += z; }

	camera->rotateCamera(i, i, k);

	if (mouseXY > window->getWindowWidth() - window->getWindowWidth() / 40)
	{
		mouseXY = window->getWindowWidth() / 2;
		glutWarpPointer(window->getWindowWidth() / 2, mouseZ);
	}
	if (mouseXY < window->getWindowWidth() / 40)
	{
		mouseXY = window->getWindowWidth() / 2;
		glutWarpPointer(window->getWindowWidth() / 2, mouseZ);
	}
	if (mouseZ > window->getWindowHeight() - window->getWindowHeight() / 40)
	{
		mouseZ = window->getWindowHeight() / 2;
		glutWarpPointer(mouseXY, window->getWindowHeight() / 2);
	}
	if (mouseZ < window->getWindowHeight() / 40)
	{
		mouseZ = window->getWindowHeight() / 2;
		glutWarpPointer(mouseXY, window->getWindowHeight() / 2);
	}
}

void singleShot()
{
	mixer->playGunShotSerie();
}

void serieShot()
{
	canShotFlag = false;
	shotFlag = true;

	while (shotFlag)
	{
		singleShot();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	canShotFlag = true;
}

void shotStop()
{
	shotFlag = false;
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN || leapManager->isKeyActive(KEY_VIRTUAL_LEFT_MOUSE_BUTTON))
	{
		if (canShotFlag)
		{
			std::thread first(serieShot);
			first.detach();
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP || !leapManager->isKeyActive(KEY_VIRTUAL_LEFT_MOUSE_BUTTON)){ shotStop(); }
	else if (button == GLUT_MIDDLE_BUTTON){}
	else if (button == GLUT_RIGHT_BUTTON){}
}


//Procedura uruchamiana okresowo. Robi animacjê.
void nextFrame(void) {
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle > 360) angle -= 360;


	/*Hand left = controller->frame().hands().leftmost();
	Hand right = controller->frame().hands().rightmost();*/

	//leapManager->fireMotionListeners();

	virtualMouseMove();
	keyPressed(0, 0, 0);
	mouseClick(3333, 3333, 3333, 3333);


	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	camera = new Camera();
	window = new Window(100, 100, 860, 484, "No Life v1.0");

	OpenGLHelper::initOpenGL(&argc, argv, window->getWindowName(), window->getXPosition(), window->getYPosition(), window->getWindowWidth(), window->getWindowHeight());
	OpenGLHelper::registerWindowResizeProcedure([](int width, int height)-> void { window->setWindowDimensions(width, height); });
	OpenGLHelper::registerDisplayFrameProcedure(displayFrame);
	OpenGLHelper::registerAnimationProcedure(nextFrame);

	keyboard = new Keyboard();
	keyboard->addKeyUpListener(keyUp);
	keyboard->addKeyDownListener(keyDown);
	keyboard->addKeyDownListener(keyPressed);

	Scene::getInstance().initScene();

	environmentPainter = new EnvironmentPainter();
	guiPainter = new GuiPainter();
	simpleObjectsPainter = new ObjectPainter();
	weaponPainter = new WeaponPainter();

	glutKeyboardFunc([](unsigned char c, int x, int y) { keyboard->keyDown(c, x, y); });
	glutKeyboardUpFunc([](unsigned char c, int x, int y) { keyboard->keyUp(c, x, y); });
	glutSpecialFunc([](int c, int x, int y) { keyboard->keyFunctionalDown(c, x, y); });
	glutSpecialUpFunc([](int c, int x, int y) { keyboard->keyFunctionalDown(c, x, y); });
	glutPassiveMotionFunc(passiveMouseMove);
	glutMotionFunc(passiveMouseMove);
	glutMouseFunc(mouseClick);
	glutSetCursor(GLUT_CURSOR_NONE);

	floore = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects/\\floor.obj", "resources\\models\\textures\\terrain.tga");

	skydome = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\skydome2.obj", "resources\\models\\textures\\skydome2.tga");
	skydome->instantScale(0.5, 0.5, 0.5);

	environmentObjects = new vector < Drawable* > ;
	environmentObjects->push_back(floore);
	environmentObjects->push_back(skydome);

	demon = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\devil.obj");
	demon->changeColor(0.9, 0.0, 0.0);
	demon->instantMove(5.0, 5.0, 0.0);

	USS = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\fog.obj", "resources\\models\\textures\\mist.tga");
	USS->instantMove(-20, 20, 0);

	smallDragon = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\small_dragon.obj");
	smallDragon->changeColor(0.4, 0.2, 0.1);
	smallDragon->instantScaleNatural(15.0);
	smallDragon->instantRotate(-90.0f, -90.0f, .0f);
	smallDragon->instantMove(-20.0, 10.0, 15.0);

	house = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\house.obj");
	house->changeColor(0.3, 0.2, 0.3);
	house->instantMove(50.0, 40.0, 0.0);

	kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\cz805.obj", "resources\\models\\textures\\CZ805.tga");
	kostka->instantScale(0.35, 0.35, 0.35);
	kostka->instantMove(0, 2, 0.2);

	simpleObjects = new vector<Drawable*>();
	simpleObjects->push_back(kostka);
	simpleObjects->push_back(house);
	simpleObjects->push_back(smallDragon);
	simpleObjects->push_back(USS);
	simpleObjects->push_back(demon);


	obj2D = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_CIRCLE);
	obj2D->instantScaleNatural(0.12f);
	obj2D->instantRotate(180.0);
	obj2D->instantMove(0.85*window->getWindowWidth() / window->getWindowHeight(), -0.75);

	crosshair = new Crosshair();

	guiObjects = new vector < Drawable*>();
	guiObjects->push_back(obj2D);
	guiObjects->push_back(crosshair);

	weapon = new DrawableObject(Scene::getInstance().shaderProgramEyePerspective, "resources\\models\\objects\\cz805.obj", "resources\\models\\textures\\CZ805.tga");
	weapon->changeColor(0.1, 0.1, 0.1);
	weapon->instantRotate(0, 5, 95);
	weapon->instantMove(0.7, -2.2, -1);
	weapon->instantScale(0.4, 0.4, 0.4);


	mixer = new MusicMixer();
	mixer->playBackgroundMusic();

	leapManager = new LeapMotionManager();

	controller = new Controller();
	controller->addListener(*leapManager);

	/*leapManager->addMotionListener([](LeapMotionManager* lm)
	{
	virtualMouseMove();
	keyPressed(0, 0, 0);
	mouseClick(3333, 3333, 3333, 3333);
	});*/

	glutMainLoop();

	controller->removeListener(*leapManager);

	return 0;
}
