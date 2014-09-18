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

using namespace std;

Window *window;
Camera *camera;
Scene &scene = Scene::getInstance();
MusicMixer *mixer;

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


bool keyW = false, keyS = false, keyA = false, keyD = false, keyE = false, keyShift = false, keySpace = false, keyZ = false, keyX = false, keyC = false;
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

//Procedura uruchamiana okresowo. Robi animacjê.
void nextFrame(void) {
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle > 360) angle -= 360;
	glutPostRedisplay();
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

	if (keyW)
	{
		if (keyE)
		{
			j += 0.6;
			obsZ = 1.8 + sin(j) / 8;

			stepX = (pktX - obsX) / 60;
			stepY = (pktY - obsY) / 60;
		}
		else
		{
			stepX = (pktX - obsX) / 100;
			stepY = (pktY - obsY) / 100;
		}

		obsX += stepX;
		obsY += stepY;
		pktX += stepX;
		pktY += stepY;

		skydome->instantMove(stepX, stepY, 0);
	}
	if (keyS)
	{
		stepX = (pktX - obsX) / 100;
		stepY = (pktY - obsY) / 100;

		if (keyE)
		{
			j += 0.6;
			obsZ = 1.8 + sin(j) / 8;

			stepX = (pktX - obsX) / 60;
			stepY = (pktY - obsY) / 60;
		}
		else
		{
			stepX = (pktX - obsX) / 100;
			stepY = (pktY - obsY) / 100;
		}

		obsX -= stepX;
		obsY -= stepY;
		pktX -= stepX;
		pktY -= stepY;

		skydome->instantMove(-stepX, -stepY, 0);
	}
	if (keyA)
	{
		stepX = -(pktY - obsY) / 100;
		stepY = (pktX - obsX) / 100;

		obsX -= stepX;
		obsY -= stepY;
		pktX -= stepX;
		pktY -= stepY;

		skydome->instantMove(-stepX, -stepY, 0);

	}
	if (keyD)
	{
		stepX = -(pktY - obsY) / 100;
		stepY = (pktX - obsX) / 100;

		obsX += stepX;
		obsY += stepY;
		pktX += stepX;
		pktY += stepY;

		skydome->instantMove(stepX, stepY, 0);
	}

	camera->setPosition(obsX, obsY, obsZ);
	camera->setLookAtPoint(pktX, pktY, pktZ);
}


void keyDown(unsigned char c, int x, int y)
{
	if (c == 'w') { keyW = true; }
	else if (c == 's') { keyS = true; }
	else if (c == 'a') { keyA = true; }
	else if (c == 'd') { keyD = true; }
	else if (c == 'e') { keyE = true; }
	else if (c == 'z') { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f); }
	else if (c == 'x') { camera->setPosition(camera->getXPosition(), camera->getYPosition(), 1.0f); }
	else if (c == 'c') { camera->setPosition(camera->getXPosition(), camera->getZPosition(), 0.5f); }

	keyPressed(c, x, y);
}

void jump()
{
	float obsZ = camera->getZPosition();
	for (float i = 0.0f; i < 3.14f; i += 0.1f)
	{
		jumpFlag = false;
		obsZ = 2.0f + sin(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		jumpFlag = true;

		camera->setPosition(camera->getXPosition(), camera->getYPosition(), obsZ);
	}

	camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f);
}

void keyDown(int c, int x, int y)
{
	if (c = GLUT_KEY_SHIFT_L) { keyShift = true; }

	keyPressed((char)c, x, y);
}

void keUp(unsigned char c, int x, int y)
{
	if (c == 'w'){ keyW = false; }
	else if (c == 's') { keyS = false; }
	else if (c == 'a') { keyA = false; }
	else if (c == 'd') { keyD = false; }
	else if (c == 'e')
	{
		keyE = false;
		camera->setPosition(camera->getXPosition(), camera->getYPosition(), 2.0f);
	}
	else if (c == ' ')
	{
		if (jumpFlag)
		{
			std::thread first(jump);
			first.detach();
		}
	}
	else if (c == 'n') { mixer->playBackgroundMusic(); }
	else if (c == 'm')
	{
		if (mixer->getBackgroundMusicVolume() < 0.02f) { mixer->enableBackgroundMusic(); }
		else { mixer->muteBackgroundMusic(); }
	}
}

void keyUp(int c, int x, int y)
{
	if (c = GLUT_KEY_SHIFT_L) { keyShift = false; }
}

void passiveMouseMove(int x, int y)
{
	int xy = x;// -windowWidth / 2;
	int z = y;// -windowHeight / 2;

	xy = xy - mouseXY;
	z = z - mouseZ;

	mouseXY = x;
	mouseZ = y;

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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (canShotFlag)
		{
			std::thread first(serieShot);
			first.detach();
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){ shotStop(); }
	else if (button == GLUT_MIDDLE_BUTTON){}
	else if (button == GLUT_RIGHT_BUTTON){}
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

	Scene::getInstance().initScene();

	environmentPainter = new EnvironmentPainter();
	guiPainter = new GuiPainter();
	simpleObjectsPainter = new ObjectPainter();
	weaponPainter = new WeaponPainter();

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keUp);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMouseMove);
	glutMotionFunc(passiveMouseMove);
	glutMouseFunc(mouseClick);
	glutSetCursor(GLUT_CURSOR_NONE);

	floore = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects/\\floor.obj", "resources\\models\\textures\\terrain.tga");

	skydome = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\skydome2.obj", "resources\\models\\textures\\skydome2.tga");
	skydome->instantScale(0.5, 0.5, 0.5);

	environmentObjects = new vector<Drawable*>;
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

	glutMainLoop();

	return 0;
}
