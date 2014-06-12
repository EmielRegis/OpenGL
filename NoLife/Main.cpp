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





using namespace std;

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





bool artificalMousemove = false;

Scene &scene = Scene::getInstance();
//Macierze

bool keyW = false, keyS = false, keyA = false, keyD = false, keyE = false, keyShift = false, keySpace = false, keyZ = false, keyX = false, keyC = false;

//Ustawienia okna i rzutowania
int windowPositionX = 100;
int windowPositionY = 100;
int windowWidth = 860;
int windowHeight = 484;
float cameraAngle = 45.0f;

float weaponRotationFlag = true;

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
	glClearColor(0.5, 0.1, 0.8, 0.7);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)windowWidth / (float)windowHeight, 1.0f, 200.0f);

	//Wylicz macierz widoku
	scene.matV = glm::lookAt(glm::vec3(obsX, obsZ, obsY), //skad dom 0,0, 7
		glm::vec3(pktX, pktZ, pktY), //dokad dom 0,0,0
		glm::vec3(0.0f, 1.0f, 0.0f)); //  jaki kat - domyslnie gora-dol

	

	scene.matM = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 1, 0));
	scene.matM = glm::translate(scene.matM, glm::vec3(0.0, 2.0, 0.0));
	kostka->drawObject();

	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, 0.0, 20.0));
	scene.matM = glm::rotate(scene.matM, angle, glm::vec3(0.0, 1, 0));	
	USS->drawObject();

	//scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0, 0.0));
	

	demon->drawObject();
		
	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, 10.0, 15.0));
	scene.matM = glm::scale(scene.matM, glm::vec3(15.0, 15.0, 15.0));
	scene.matM = glm::rotate(scene.matM, 90.0f, glm::vec3(1.0, .0, 0.0));
	scene.matM = glm::rotate(scene.matM, 180.0f, glm::vec3(1.0, 1.0, 0.0));
	smallDragon->drawObject();
	
	house->drawObject();



	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)windowWidth / (float)windowHeight, 0.0125f, 400.0f);

	floore->drawObject();
	skydome->drawObject();

	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)windowWidth / (float)windowHeight, 1.0f, 200.0f);

	weapon->drawObject();

	//weapon->instantMove(obsX - weapon->getXCoordinate(), obsY - weapon->getYCoordinate(), 0.0);
	

	

	scene.matP = glm::mat4((float)windowHeight / windowWidth, 0.0f, 0.0f, 0.0f,
		0.0f, (float)windowHeight / windowHeight, 0.0f, 0.0f,
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
		windowWidth = w;
		windowHeight = w * 10 / 16;	
	}
	else if (w > h * 22/10)
	{
		windowWidth = h * 22 / 10;
		windowHeight = h;
	}
	else
	{
		windowWidth = w;
		windowHeight = h;
	}

	glViewport(0, 0, windowWidth, windowHeight);
}


//Procedura inicjuj¹ca biblotekê glut
void initGLUT(int *argc, char** argv) {
	glutInit(argc, argv); //Zainicjuj bibliotekê GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolorów (podwójne buforowanie) i bufor kolorów

	glutInitWindowPosition(windowPositionX, windowPositionY); //Wska¿ pocz¹tkow¹ pozycjê okna
	glutInitWindowSize(windowWidth, windowHeight); //Wska¿ pocz¹tkowy rozmiar okna
	glutCreateWindow("OpenGL 3.3"); //Utwórz okno i nadaj mu tytu³

	glutReshapeFunc(changeSize); //Zarejestruj procedurê changeSize jako procedurê obs³uguj¹ca zmianê rozmiaru okna
	glutDisplayFunc(displayFrame); //Zarejestruj procedurê displayFrame jako procedurê obs³uguj¹ca odœwierzanie okna
	glutIdleFunc(nextFrame); //Zarejestruj procedurê nextFrame jako procedurê wywo³ywan¹ najczêœciêj jak siê da (animacja)
}


//Procedura inicjuj¹ca bibliotekê glew
void initGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		exit(1);
	}

}


/*//Wczytuje vertex shader i fragment shader i ³¹czy je w program cieniuj¹cy
void setupShaders() {
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
}*/




/*//Zwolnij pamiêæ karty graficznej z shaderów i programu cieniuj¹cego
void cleanShaders() {
	delete shaderProgram;
}*/












// kontrola naciskania klawiszy klawiatury
void keyPressed(unsigned char key, int x, int y)
{



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


	if (weaponRotationFlag)
	{
		//weapon->instantRotateAroundPoint(0.0, 0.0, (((acos((pktX - obsX) / R))*57.29578 - 180.0) - weapon->getZRotationAroundAngle() + 200.0), 1.3, 1.2, 0.0);
		//weaponRotationFlag = false;
	}
	else
	{
		float sinD = (asin((pktY - obsY) / R))*57.29578;
		float cosD = (acos((pktX - obsX) / R))*57.29578 - 180.0;

		if (cosD < 0 && sinD > 0)
		{
			cosD = -cosD;
		}

		float d = 0;
		d = ((cosD - weapon->getZRotationAroundAngle() + 200.0));
	
		//cout << "xy: " << -xy << " d: " << d << " coskat: " << cosD << " sinkat: " << sinD << " kat broni: " << weapon->getZRotationAroundAngle() << endl;

		//weapon->instantRotateAroundPoint(0.0, 0.0, d, 1.3, 1.2, 0.0);
		//weapon->instantRotate(0.0,acos((((pktZ - obsZ) / R))*57.29578) - weapon->getYRotationAngle(), 0.0);

		// cout << acos((((pktZ - obsZ) / R))*57.29578) - 180.0 << endl;
		
	}
	
	


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

	if (mouseXY > windowWidth - windowWidth/40)
	{
		mouseXY = windowWidth / 2;
		glutWarpPointer(windowWidth / 2, mouseZ);
	}
	if (mouseXY < windowWidth / 40)
	{
		mouseXY = windowWidth / 2;
		glutWarpPointer(windowWidth / 2, mouseZ);
	}
	if (mouseZ > windowHeight - windowHeight / 40)
	{
		mouseZ = windowHeight / 2;
		glutWarpPointer(mouseXY, windowHeight / 2);
	}
	if (mouseZ < windowHeight / 40)
	{
		mouseZ = windowHeight / 2;
		glutWarpPointer(mouseXY, windowHeight / 2);
	}
	
}

bool shotFlag = false;

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
	
	

	initGLUT(&argc, argv);
	//initGLUT(0, NULL);
	initGLEW();
	//setupShaders();
	Scene::getInstance().initScene();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keUp);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMouseMove);
	glutMouseFunc(mouseClick);

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_LIGHTING);
	// w³¹czenie obs³ugi w³aœciwoœci materia³ów
	glEnable(GL_COLOR_MATERIAL);
	// w³¹czenie testu bufora g³êbokoœci
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	GLint textureUnits = 3;	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);


	//kostka = new DrawableObject(shaderProgram, "cube1.obj");
	//malpa = new DrawableObject(shaderProgram, "floor.obj");
	//malpa->changeColor(0.1f, 0.4f, 0.1f);
	floore = new DrawableObject(Scene::getInstance().shaderProgramProTex, "floor.obj", "terrain.tga");
	//floore = new DrawableObject(Scene::getInstance().shaderProgramProTex, "skydome.obj", "skydome.tga");
	floore->setAlternativeDrawing(true);
	//floore->changeColor(0.4, 0.7, 0.4);

	skydome = new DrawableObject(Scene::getInstance().shaderProgramProTex, "skydome2.obj", "skydome2.tga");
	skydome->setAlternativeDrawing(true);
	skydome->instantScale(0.5, 0.5, 0.5);

	demon = new DrawableObject(Scene::getInstance().shaderProgramPro, "devil.obj");
	demon->changeColor(0.9, 0.0, 0.0);
	demon->setAlternativeDrawing(true);
	demon->instantMove(20.0, 10.0, 0.0);
	
	
	USS = new DrawableObject(Scene::getInstance().shaderProgramProTex, "USSEnterprise.obj", "uss.tga");

	

	smallDragon = new DrawableObject(Scene::getInstance().shaderProgramPro, "small_dragon.obj");
	smallDragon->changeColor(0.4, 0.2, 0.1);
	

	house = new DrawableObject(Scene::getInstance().shaderProgramPro, "house.obj");
	house->setAlternativeDrawing(true);
	house->changeColor(0.3, 0.2, 0.3);
	house->instantMove(50.0, 40.0, 0.0);

	

	//kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "wood_cube2.obj", "wood.tga");
	kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "cz805.obj", "CZ805.tga");

	

	obj2D = new DrawableObject2D(Scene::getInstance().shaderProgram2D, DrawableObject2D::DRAWABLE_2D_PRIMITIVE_CIRCLE);
	obj2D->instantScaleNatural(0.12f);
	obj2D->instantRotate(180.0);
	obj2D->instantMove(0.85*windowWidth/windowHeight, -0.75);

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


	weapon = new DrawableObject(Scene::getInstance().shaderProgramEyePerspective, "cz805.obj", "CZ805.tga");
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

	new DrawableObject(Scene::getInstance().shaderProgramPro, "mp5.obj", 2, "dfdf", "fdfdf");


	
	


	glutMainLoop();

	//cleanShaders();
	return 0;
}
