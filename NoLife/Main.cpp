#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "tga/tga.h"
#include "shaderprogram.h"
#include "cube.h"
#include "teapot.h"
#include "vector"
#include <ios>
#include <sstream>
#include "Scene.h"
#include "DrawableObject.h"


using namespace std;

DrawableObject *kostka;
DrawableObject *malpa;

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
float obsX = 20.0f, obsY = 20.0f, obsZ = 3.0f, pktX = -8, pktY = 80.0f, pktZ = 1.0f, stepX = 0.0f, stepY = 0.0f, stepZ = 0.0f,
i = 225,
k = 90,
j = 0,
N = 360,
R = abs(obsX - pktX);

int mouseXY = 0, mouseZ;

//Uchwyty na shadery
ShaderProgram *shaderProgram; //WskaŸnik na obiekt reprezentuj¹cy program cieniuj¹cy.

//Uchwyty na VAO i bufory wierzcho³ków
GLuint vao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowuj¹cy tablicê wspó³rzêdnych wierzcho³ków
GLuint bufColors;  //Uchwyt na bufor VBO przechowuj¹cy tablicê kolorów
GLuint bufNormals; //Uchwyt na bufor VBO przechowuj¹cy tablicê wektorów normalnych
GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablicê wartoœci tekstur
GLuint bufElements; //Uchwyt na bufor VBO elementow - trojkatow o ile takowy bufor mozna utworzyc

//"Model" który rysujemy. Dane wskazywane przez poni¿sze wskaŸniki i o zadanej liczbie wierzcho³ków s¹ póŸniej wysowane przez program.
//W programie s¹ dwa modele, z których jeden mo¿na wybraæ komentuj¹c/odkomentowuj¹c jeden z poni¿szych fragmentów.

//Kostka
/*float *vertices = cubeVertices;
float *colors = cubeColors;
float *normals = cubeNormals;
int vertexCount = cubeVertexCount;*/

/*
//Czajnik
float *vertices=teapotVertices;
float *colors=teapotColors;
float *normals=teapotNormals;
int vertexCount=teapotVertexCount;*/

float *vertices;
float *colors;
float *normals;
float *textures;
GLushort *elements;
int vertexCount;

vector<float> suzanne_vertices;
vector<float> suzanne_normals;
vector<float> suzanne_colors;
vector<float> suzanne_textures;
vector<GLushort> suzanne_elements;





//Procedura rysuj¹ca
void displayFrame() {
	//Wyczyœæ bufor kolorów i bufor g³êbokoœci
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Wylicz macierz rzutowania
	scene.matP = glm::perspective(cameraAngle, // przyblizy/oddali wido
		(float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

	//Wylicz macierz widoku
	scene.matV = glm::lookAt(glm::vec3(obsX, obsZ, obsY), //skad dom 0,0, 7
		glm::vec3(pktX, pktZ, pktY), //dokad dom 0,0,0
		glm::vec3(0.0f, 1.0f, 0.0f)); //  jaki kat - domyslnie gora-dol


	//Wylicz macierz modelu
	scene.matM = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.5, 1, 0));

	//Narysuj obiekt
	kostka->drawObject();


	scene.matM = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0, 0.0));
	malpa->drawObject();



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
	glViewport(0, 0, w, h);
	//Zapamiêtanie nowych wymiarów okna dla poprawnego wyliczania macierzy rzutowania
	windowWidth = w;
	windowHeight = h;
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


//Wczytuje vertex shader i fragment shader i ³¹czy je w program cieniuj¹cy
void setupShaders() {
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
}




//Zwolnij pamiêæ karty graficznej z shaderów i programu cieniuj¹cego
void cleanShaders() {
	delete shaderProgram;
}





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
				obsZ = 1.5 + sin(j) / 5;
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
				obsZ = 1.5 + sin(j) / 5;
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
	keyPressed(c, x, y);

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


	cout << "k: " << k << "   k/N: " << k / N << "   6*k/N " << 6.28318 * k / N << "cos: " << cos(6.28318 * k / N) << endl;

	pktZ = obsX + 1 * R * cos(6.28318 * k / N);




}





int main(int argc, char** argv) {

	initGLUT(&argc, argv);
	initGLEW();
	setupShaders();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keUp);
	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMouseMove);

	kostka = new DrawableObject(shaderProgram, "suzanne.obj");
	malpa = new DrawableObject(shaderProgram, "floor.obj");

	glEnable(GL_DEPTH_TEST);



	glutMainLoop();


	cleanShaders();
	return 0;
}
