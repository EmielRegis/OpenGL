#include <windows.h> //Wymagane dla implementacji OpenGL w Visual Studio.
//#include "gl\glew.h"
#include "gl\glut.h"
#include "stdio.h" //Przydatne do wypisywania komunikatów na konsoli
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "tga\tga.h"

float speed = 360; //360 stopni/s
int lastTime = 0;
float angle;

using namespace glm;


void displayFrame(void) {
	//Wyczyszczenie okna
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Obliczenie macierzy rzutowania
	glm::mat4 P = glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);

	//Obliczenie macierzy widoku (de fact ustawienie kamery na scenie);
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	//Za³adowanie macierzy rzutowania do OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));

	//Przygotowanie do ³adowania macierzy widoku i modelu
	glMatrixMode(GL_MODELVIEW);


	//Rysowanie obiektu (mozna to wykonaæ w pêtli dla wielu obiektów)
	//1. Wyliczenie jego macierzy modelu
	glm::mat4 M1 = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-2.1, 0, 0)), angle, glm::vec3(0.0f, 0.0f, 1.0f));
	//2. Za³adowanie macierzy do OpenGL
	glLoadMatrixf(glm::value_ptr(V*M1));
	//3. Rysowanie obiektu
	glColor3f(1, 0.5, 0.2);
	glutSolidTorus(0.5, 1.5, 30, 30);

	for (int i = 0; i <= 330; i += 30)
	{
		mat4 Mi = translate(rotate(M1, (float)i, vec3(0.0f, 0.0f, 1.0f)), vec3(1.9, 0.0, 0.0));
		glLoadMatrixf(glm::value_ptr(V*Mi));
		glColor3f(1, 0.5, 0.2);
		glutSolidCube(0.5);

	}


	//Rysowanie obiektu (mozna to wykonaæ w pêtli dla wielu obiektów)
	//1. Wyliczenie jego macierzy modelu
	glm::mat4 M2 = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(2.1, 0, 0)), -angle, glm::vec3(0.0f, 0.0f, 1.0f));
	//2. Za³adowanie macierzy do OpenGL
	glLoadMatrixf(glm::value_ptr(V*M2));
	//3. Rysowanie obiektu
	glColor3f(1, 0.5, 0.2);
	glutSolidTorus(0.5, 1.5, 20, 20);


	for (int i = 15; i <= 345; i += 30)
	{
		mat4 Mi = translate(rotate(M2, (float)i, vec3(0.0f, 0.0f, 1.0f)), vec3(1.9, 0.0, 0.0));
		glLoadMatrixf(glm::value_ptr(V*Mi));
		glColor3f(1, 0.5, 0.2);
		glutSolidCube(0.5);

	}


	//Przerzucenie tylnego bufora na przedni
	glutSwapBuffers();
}


void nextFrame(void) {
	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;
	angle += speed*interval / 1000.0;
	if (angle>360) angle -= 360;
	glutPostRedisplay();
}

void keyDown(int c, int x, int y)
{
	if (c == GLUT_KEY_RIGHT)
	{
		speed = 360;
	}
	else if (c == GLUT_KEY_LEFT)
	{
		speed = -360;
	}
}

void keyUp(int c, int x, int y)
{
	speed = 0;
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Program OpenGL");
	glutDisplayFunc(displayFrame);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	glutIdleFunc(nextFrame);

	//Tutaj kod inicjuj¹cy
	//glewInit();


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glutMainLoop();
	return 0;
}