#pragma once
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "tga/tga.h"
#include "shaderprogram.h"

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

using namespace std;

Window *window;
Camera *camera;
Scene &scene = Scene::getInstance();
MusicMixer *mixer;

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
DrawableObject2D *crossA;
DrawableObject2D *crossB;
DrawableObject2D *crossC;
DrawableObject2D *crossD;

bool keyW = false, keyS = false, keyA = false, keyD = false, keyE = false, keyShift = false, keySpace = false, keyZ = false, keyX = false, keyC = false;
float cameraAngle = 45.0f;
bool shotFlag = false;

//Zmienne do animacji
float speed = 120; //120 stopni/s
int lastTime = 0;
float angle = 0;

// zmienne do poruszania sie
float obsX = 10.0f, obsY = 0.0f, obsZ = 2.0f, pktX = -8, pktY = -18.0f, pktZ = 2.0f, stepX = 0.0f, stepY = 0.0f, stepZ = 0.0f,
i = 225,
k = 90,
j = 0,
N = 360,
R = abs(obsX - pktX);

int mouseXY = 0, mouseZ;

//Uchwyty na VAO i bufory wierzcho³ków
GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowuj¹cy tablicê wspó³rzêdnych wierzcho³ków
GLuint bufColors;  //Uchwyt na bufor VBO przechowuj¹cy tablicê kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowuj¹cy tablicê wektorów normalnych
GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablicê wartoœci tekstur
GLuint bufElements; //Uchwyt na bufor VBO elementow - trojkatow o ile takowy bufor mozna utworzyc

//Procedura rysuj¹ca
void displayFrame() {
	//Wyczyœæ bufor kolorów i bufor g³êbokoœci
	glClearColor(1.0, 1.0, 1.0, 0.1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)window->getWindowWidth() / (float)window->getWindowHeight(), 1.0f, 200.0f);

	//Wylicz macierz widoku
	scene.matV = glm::lookAt(glm::vec3(obsX, obsZ, obsY), //skad dom 0,0, 7
		glm::vec3(pktX, pktZ, pktY), //dokad dom 0,0,0
		glm::vec3(0.0f, 1.0f, 0.0f)); //  jaki kat - domyslnie gora-dol


	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)window->getWindowWidth() / (float)window->getWindowHeight(), 0.0125f, 400.0f);

	floore->drawObject();
	skydome->drawObject();


	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)window->getWindowWidth() / (float)window->getWindowHeight(), 1.0f, 200.0f);
	

	kostka->instantRotate(0, 0, angle - kostka->getZRotationAngle());
	kostka->drawObject();

	USS->instantRotate(0, 0, angle - USS->getZRotationAngle());
	USS->drawObject();


	demon->drawObject();

		
	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, 10.0, 15.0));
	scene.matM = glm::scale(scene.matM, glm::vec3(15.0, 15.0, 15.0));
	scene.matM = glm::rotate(scene.matM, 90.0f, glm::vec3(1.0, .0, 0.0));
	scene.matM = glm::rotate(scene.matM, 180.0f, glm::vec3(1.0, 1.0, 0.0));
	smallDragon->drawObject();
	
	house->drawObject();



	

	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)window->getWindowWidth() / (float)window->getWindowHeight(), 1.0f, 200.0f);

	weapon->drawObject();

	//weapon->instantMove(obsX - weapon->getXCoordinate(), obsY - weapon->getYCoordinate(), 0.0);
	

	

	scene.matP = glm::mat4((float)window->getWindowHeight() / window->getWindowWidth(), 0.0f, 0.0f, 0.0f,
		0.0f, (float)window->getWindowHeight() / window->getWindowHeight(), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	
	obj2D->drawObject();

	crossA->drawObject();
	crossB->drawObject();
	crossC->drawObject();
	crossD->drawObject();


	



	//Tylny bufor na przedni
	glutSwapBuffers();
}

//Procedura uruchamiana okresowo. Robi animacjê.
void nextFrame(void) {
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle>360) angle -= 360;
	glutPostRedisplay();
}

//Procedura wywo³ywana przy zmianie rozmiaru okna
void changeSize(int w, int h) {
	//Ustawienie wymiarow przestrzeni okna
	
	//Zapamiêtanie nowych wymiarów okna dla poprawnego wyliczania macierzy rzutowania
	if (h > w * 10 / 16)
	{
		window->setWindowDimensions(w, w * 10 / 16);
	}
	else if (w > h * 22/10)
	{
		window->setWindowDimensions(h * 22 / 10, h);
	}
	else
	{
		window->setWindowDimensions(w, h);
	}

	glViewport(0, 0, window->getWindowWidth(), window->getWindowHeight());
}

void playerMoveListener()
{
	glm::vec3 look = glm::vec3(0, 0, 1);
	float lookLength = glm::sqrt(look.x*look.x + look.z*look.z + look.y*look.y);

	glm::vec3 objToCam = glm::normalize(glm::vec3(obsX, 0, obsY) - glm::vec3(demon->getXCoordinate(), 0, demon->getYCoordinate()));
	float objToCamLength = glm::sqrt(objToCam.x*objToCam.x + objToCam.z*objToCam.z + objToCam.y*objToCam.y);

	float deg = glm::degrees(acos(glm::dot(look, objToCam) / (glm::abs(lookLength) * glm::abs(objToCamLength))));

	if (obsX < 0)
	{
		deg = -deg;
	}

	demon->instantRotate(0, 0, deg - demon->getZRotationAngle());
}

// kontrola naciskania klawiszy klawiatury
void keyPressed(unsigned char key, int x, int y)
{
	playerMoveListener();


	//switch (key)
	{
		//case 37: {rot_y -= 5.0f; break; }
		//case 38: {rot_x -= 5.0f; break; }
		//case 39: {rot_y += 5.0f; break; }
		//case 40: {rot_x += 5.0f; break; }

		//case 87:
		if (keyW){


			
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
			// break;

		} // w
		//case 83:
		if (keyS){

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
			// break;
		} // sy
		//case 65:
		if (keyA){
			stepX = -(pktY - obsY) / 100;
			stepY = (pktX - obsX) / 100;

			obsX -= stepX;
			obsY -= stepY;
			pktX -= stepX;
			pktY -= stepY;

			skydome->instantMove(-stepX, -stepY, 0);

		} // a
		if (keyD)//case 68:
		{
			stepX = -(pktY - obsY) / 100;
			stepY = (pktX - obsX) / 100;

			obsX += stepX;
			obsY += stepY;
			pktX += stepX;
			pktY += stepY;


			skydome->instantMove(stepX, stepY, 0);
		} // d

	}

}

void keyDown(unsigned char c, int x, int y)
{
	if (c == 'w')
	{
		keyW = true;
	}
	else if (c == 's')
	{
		keyS = true;
	}
	else if (c == 'a')
	{
		keyA = true;
	}
	else if (c == 'd')
	{
		keyD = true;
	}
	else if (c == 'e')
	{
		keyE = true;
		
	}
	else if (c == 'z')
	{
		obsZ = 2.0f;
	}
	else if (c == 'x')
	{
		obsZ = 1.0f;
	}
	else if (c == 'c')
	{
		obsZ = 0.5f;
	}
	keyPressed(c, x, y);

}

bool jumpFlag = true;

void jump()
{
	for (float i = 0.0f; i < 3.14f; i += 0.1f)
	{
		jumpFlag = false;
		obsZ = 2.0f + sin(i);
		//weapon->instantMove(0, 0 ,0.65 + sin(i) - weapon->getZCoordinate());
		//cout << obsZ << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		jumpFlag = true;
		

	}

	obsZ = 2.0;
}

void keyDown(int c, int x, int y)
{
	if (c = GLUT_KEY_SHIFT_L)
	{
		keyShift = true;
	}


	keyPressed((char)c, x, y);
}

void keUp(unsigned char c, int x, int y)
{
	if (c == 'w')
	{
		keyW = false;
	}
	else if (c == 's')
	{
		keyS = false;
	}
	else if (c == 'a')
	{
		keyA = false;
	}
	else if (c == 'd')
	{
		keyD = false;
	}
	else if (c == 'e')
	{
		keyE = false;
		obsZ = 2.0f;
	}
	else if (c == ' ')
	{
		if (jumpFlag)
		{
			std::thread first(jump);
			first.detach();
		}	
	}
	else if (c == 'n')
	{
		mixer->playBackgroundMusic();
	}
	else if (c == 'm')
	{
		if (mixer->getBackgroundMusicVolume() < 0.02f)
		{
			mixer->enableBackgroundMusic();
		}
		else
		{
			mixer->muteBackgroundMusic();
		}
	}
}

void keyUp(int c, int x, int y)
{
	if (c = GLUT_KEY_SHIFT_L)
	{
		keyShift = false;
	}
}

void passiveMouseMove(int x, int y)
{
	

	int xy = x;// -windowWidth / 2;
	int z = y;// -windowHeight / 2;

	xy = xy - mouseXY;
	z = z - mouseZ;




	mouseXY = x;
	mouseZ = y;

	if (i > 0)
	{
		i += xy;
	}
	else
	{
		i = 360;
	}
	pktX = obsX + 1 * R * cos(6.28318 * i / N);
	pktY = obsY + 1 * R * sin(6.28318 * i / N);

	if (k > 10)
	{
		if ((k < 180) && k >= -z && (180 - k) >= z)
		{
			k += z;
		}
		else
		{
			if ((z < 0))
			{
				k += z;
			}
		}
	}
	else
	{
		if (z > 0)
		{
			k += z;
		}
	}

	float cosY = (acos(cos(6.28318 * k / N)))*57.29578 - 90.0;
	//cout << (acos(cos(6.28318 * k / N)))*57.29578 - 90.0 << endl;
	//weapon->instantRotate(0.0, (cosY - weapon->getYRotationAngle())*0.7, 0.0);
	//weapon->instantMove(0, 0.0, -cosY / 70.0 - weapon->getZCoordinate() + 0.65);

	//cout << "k: " << k << "   k/N: " << k / N << "   6*k/N " << 6.28318 * k / N << "cos: " << cos(6.28318 * k / N) << endl;

	pktZ = obsZ + 1 * R * cos(6.28318 * k / N);

	if (mouseXY > window->getWindowWidth() - window->getWindowWidth()/40)
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
	shotFlag = true;
	while (shotFlag)
	{
		singleShot();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void shotStop()
{
	shotFlag = false;
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		std::thread first(serieShot);
		first.detach();
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		shotStop();
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{

	}
	else if (button == GLUT_RIGHT_BUTTON)
	{

	}
}


int main(int argc, char** argv) {

	srand(time(NULL));
	
	window = new Window();
	
	OpenGLHelper::initOpenGL(&argc, argv, window->getXPosition(), window->getYPosition(), window->getWindowWidth(), window->getWindowHeight());
	OpenGLHelper::registerWindowResizeProcedure(changeSize);
	OpenGLHelper::registerDisplayFrameProcedure(displayFrame);
	OpenGLHelper::registerAnimationProcedure(nextFrame);

	camera = new Camera();
	Scene::getInstance().initScene();
	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keUp);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMouseMove);
	glutMouseFunc(mouseClick);
	glutSetCursor(GLUT_CURSOR_NONE);


	floore = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects/\\floor.obj", "resources\\models\\textures\\terrain.tga");
	floore->setAlternativeDrawing(true);

	skydome = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\skydome2.obj", "resources\\models\\textures\\skydome2.tga");
	skydome->setAlternativeDrawing(true);
	skydome->instantScale(0.5, 0.5, 0.5);

	demon = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\devil.obj");
	demon->changeColor(0.9, 0.0, 0.0);
	demon->setAlternativeDrawing(true);
	demon->instantMove(5.0, 5.0, 0.0);
	
	USS = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\fog.obj", "resources\\models\\textures\\mist.tga");
	USS->setAlternativeDrawing(true);
	USS->instantMove(-20, 20, 0);
	
	smallDragon = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\small_dragon.obj");
	smallDragon->changeColor(0.4, 0.2, 0.1);
	
	house = new DrawableObject(Scene::getInstance().shaderProgramPro, "resources\\models\\objects\\house.obj");
	house->setAlternativeDrawing(true);
	house->changeColor(0.3, 0.2, 0.3);
	house->instantMove(50.0, 40.0, 0.0);

	//kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "wood_cube2.obj", "wood.tga");
	kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "resources\\models\\objects\\cz805.obj", "resources\\models\\textures\\CZ805.tga");
	kostka->setAlternativeDrawing(true);
	kostka->instantScale(0.35, 0.35, 0.35);
	kostka->instantMove(0, 2, 0.2);
	
	obj2D = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_CIRCLE);
	obj2D->instantScaleNatural(0.12f);
	obj2D->instantRotate(180.0);
	obj2D->instantMove(0.85*window->getWindowWidth()/window->getWindowHeight(), -0.75);

	crossA = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossA->instantScaleNatural(0.3);
	crossA->instantScale(1.0, 0.1);
	crossA->instantMove(0.0, 0.05);

	crossB = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossB->instantRotate(90);
	crossB->instantScaleNatural(0.3);
	crossB->instantScale(0.1,1.0);
	crossB->instantMove(-0.05, 0.0);

	crossC = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossC->instantRotate(180);
	crossC->instantScaleNatural(0.3);
	crossC->instantScale(1.0,0.1);
	crossC->instantMove(0.0, -0.05);

	crossD = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_LINE);
	crossD->instantRotate(270);
	crossD->instantScaleNatural(0.3);
	crossD->instantScale(0.1,1.0);
	crossD->instantMove(0.05, 0.0);

	weapon = new DrawableObject(Scene::getInstance().shaderProgramEyePerspective, "resources\\models\\objects\\cz805.obj", "resources\\models\\textures\\CZ805.tga");
	weapon->setAlternativeDrawing(true);
	weapon->changeColor(0.1, 0.1, 0.1);
	//weapon->instantRotate(0, -10, 270);
	weapon->instantRotate(0, 5, 95);
	//weapon->instantMove(0.5, -1.8, -1);
	weapon->instantMove(0.7, -2.2, -1);
	//weapon->instantScale(0.7,0.7,0.7);
	weapon->instantScale(0.4, 0.4, 0.4);


	mixer = new MusicMixer();
	mixer->playBackgroundMusic();


	glutMainLoop();

	return 0;
}
