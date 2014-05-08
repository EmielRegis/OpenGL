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
#include <chrono>
#include <thread>
#include <cstdlib>



using namespace std;

DrawableObject *kostka;
DrawableObject *malpa;
DrawableObject *USS;
DrawableObject *demon;
DrawableObject *floore;
DrawableObject *smallDragon;
DrawableObject *house;

bool artificalMousemove = false;

Scene &scene = Scene::getInstance();
//Macierze

bool keyW = false, keyS = false, keyA = false, keyD = false, keyE = false, keyShift = false, keySpace = false, keyZ = false, keyX = false, keyC = false;

//Ustawienia okna i rzutowania
int windowPositionX = 100;
int windowPositionY = 100;
int windowWidth = 600;
int windowHeight = 600;
float cameraAngle = 45.0f;

//Zmienne do animacji
float speed = 120; //120 stopni/s
int lastTime = 0;
float angle = 0;

// zmienne do poruszania sie
float obsX = 20.0f, obsY = 20.0f, obsZ = 2.0f, pktX = -8, pktY = 0.0f, pktZ = 2.0f, stepX = 0.0f, stepY = 0.0f, stepZ = 0.0f,
i = 225,
k = 90,
j = 0,
N = 360,
R = abs(obsX - pktX);

int mouseXY = 0, mouseZ;



//Uchwyty na VAO i bufory wierzcho�k�w
GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowuj�cy tablic� wsp�rz�dnych wierzcho�k�w
GLuint bufColors;  //Uchwyt na bufor VBO przechowuj�cy tablic� kolor�w
GLuint bufNormals; //Uchwyt na bufor VBO przechowuj�cy tablic� wektor�w normalnych
GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablic� warto�ci tekstur
GLuint bufElements; //Uchwyt na bufor VBO elementow - trojkatow o ile takowy bufor mozna utworzyc


//Procedura rysuj�ca
void displayFrame() {
	//Wyczy�� bufor kolor�w i bufor g��boko�ci
	glClearColor(0.8, 0.8, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

	//Wylicz macierz widoku
	scene.matV = glm::lookAt(glm::vec3(obsX, obsZ, obsY), //skad dom 0,0, 7
		glm::vec3(pktX, pktZ, pktY), //dokad dom 0,0,0
		glm::vec3(0.0f, 1.0f, 0.0f)); //  jaki kat - domyslnie gora-dol


	//Wylicz macierz modelu
	scene.matM = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 1, 0));
	scene.matM = glm::translate(scene.matM, glm::vec3(0.0, 2.0, 0.0));

	kostka->drawObject();

	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, 0.0, 20.0));
	scene.matM = glm::rotate(scene.matM, angle, glm::vec3(0.0, 1, 0));
	
	USS->drawObject();

	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0, 0.0));
	floore->drawObject();


	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(20.0, 0.0, 10.0));
	demon->drawObject();
	
	
		
	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, 10.0, 15.0));
	scene.matM = glm::scale(scene.matM, glm::vec3(15.0, 15.0, 15.0));
	scene.matM = glm::rotate(scene.matM, 90.0f, glm::vec3(1.0, .0, 0.0));
	scene.matM = glm::rotate(scene.matM, 180.0f, glm::vec3(1.0, 1.0, 0.0));
	smallDragon->drawObject();

	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(50.0, 0.0, 40.0));
	house->drawObject();

	
	/*scene.matP = glm::ortho(0, windowWidth, windowHeight, 0,0, 100);
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(scene.matP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(scene.matV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(scene.matM));

	glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0, 1);
		glVertex2f(1, 1);

		glVertex2f(1, 1);
		glVertex2f(1, 0);
		glVertex2f(0, 0);
	glEnd();*/

	//Tylny bufor na przedni
	glutSwapBuffers();
}





//Procedura uruchamiana okresowo. Robi animacj�.
void nextFrame(void) {
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle>360) angle -= 360;
	glutPostRedisplay();
}


//Procedura wywo�ywana przy zmianie rozmiaru okna
void changeSize(int w, int h) {
	//Ustawienie wymiarow przestrzeni okna
	glViewport(0, 0, w, h);
	//Zapami�tanie nowych wymiar�w okna dla poprawnego wyliczania macierzy rzutowania
	windowWidth = w;
	windowHeight = h;
}


//Procedura inicjuj�ca biblotek� glut
void initGLUT(int *argc, char** argv) {
	glutInit(argc, argv); //Zainicjuj bibliotek� GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolor�w (podw�jne buforowanie) i bufor kolor�w

	glutInitWindowPosition(windowPositionX, windowPositionY); //Wska� pocz�tkow� pozycj� okna
	glutInitWindowSize(windowWidth, windowHeight); //Wska� pocz�tkowy rozmiar okna
	glutCreateWindow("OpenGL 3.3"); //Utw�rz okno i nadaj mu tytu�

	glutReshapeFunc(changeSize); //Zarejestruj procedur� changeSize jako procedur� obs�uguj�ca zmian� rozmiaru okna
	glutDisplayFunc(displayFrame); //Zarejestruj procedur� displayFrame jako procedur� obs�uguj�ca od�wierzanie okna
	glutIdleFunc(nextFrame); //Zarejestruj procedur� nextFrame jako procedur� wywo�ywan� najcz�ci�j jak si� da (animacja)
}


//Procedura inicjuj�ca bibliotek� glew
void initGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		exit(1);
	}

}


/*//Wczytuje vertex shader i fragment shader i ��czy je w program cieniuj�cy
void setupShaders() {
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
}*/




/*//Zwolnij pami�� karty graficznej z shader�w i programu cieniuj�cego
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


			stepX = (pktX - obsX) / 100;
			stepY = (pktY - obsY) / 100;
			if (keyE)
			{
				j += 0.9;
				obsZ = 1.8 + sin(j) / 5;
			}




			obsX += stepX;
			obsY += stepY;

			pktX += stepX;
			pktY += stepY;
			// break;

		} // w
		//case 83:
		if (keyS){

			stepX = (pktX - obsX) / 100;
			stepY = (pktY - obsY) / 100;


			obsX -= stepX;
			obsY -= stepY;
			if (keyE)
			{
				j += 0.9;
				obsZ = 1.8 + sin(j) / 5;
			}

			pktX -= stepX;
			pktY -= stepY;
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

		} // a
		if (keyD)//case 68:
		{
			stepX = -(pktY - obsY) / 100;
			stepY = (pktX - obsX) / 100;

			obsX += stepX;
			obsY += stepY;
			pktX += stepX;
			pktY += stepY;
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

void jump()
{
	for (float i = 0.0f; i < 3.14f; i += 0.1f)
	{
		obsZ = 2.0f + sin(i);
		//cout << obsZ << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		

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
	}
	else if (c == ' ')
	{
		std::thread first(jump);
		first.detach();

		
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
	 
	//cout  << " " << i << " " << k << endl;

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





int main(int argc, char** argv) {

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

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_LIGHTING);
	// w��czenie obs�ugi w�a�ciwo�ci materia��w
	glEnable(GL_COLOR_MATERIAL);
	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	GLint textureUnits = 3;	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);


	//kostka = new DrawableObject(shaderProgram, "cube1.obj");
	//malpa = new DrawableObject(shaderProgram, "floor.obj");
	//malpa->changeColor(0.1f, 0.4f, 0.1f);
	floore = new DrawableObject(Scene::getInstance().shaderProgramPro, "floor.obj");
	floore->changeColor(0.4, 0.7, 0.4);

	demon = new DrawableObject(Scene::getInstance().shaderProgramPro, "devil.obj");
	demon->changeColor(0.9, 0.0, 0.0);
	
	USS = new DrawableObject(Scene::getInstance().shaderProgramProTex, "USSEnterprise.obj", "uss.tga");

	

	smallDragon = new DrawableObject(Scene::getInstance().shaderProgramPro, "small_dragon.obj");
	smallDragon->changeColor(0.4, 0.2, 0.1);
	

	house = new DrawableObject(Scene::getInstance().shaderProgramPro, "house.obj");
	house->changeColor(0.3, 0.2, 0.3);

	kostka = new DrawableObject(Scene::getInstance().shaderProgramProTex, "wood_cube2.obj", "wood.tga");

	glutMainLoop();


	//cleanShaders();
	return 0;
}
