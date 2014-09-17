#include "OpenGLHelper.h"



OpenGLHelper::OpenGLHelper()
{
}


OpenGLHelper::~OpenGLHelper()
{
}

void OpenGLHelper::initOpenGL(int *argc, char** argv, string windowCaption, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight)
{
	initGLUT(argc, argv, windowCaption, windowXPosition, windowYPosition, windowWidth, windowHeight);
	initGLEW();	

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	GLint textureUnits = 3;	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
}

//Procedura inicjuj�ca biblotek� glut
void OpenGLHelper::initGLUT(int *argc, char** argv, string windowCaption, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight) {
	glutInit(argc, argv); //Zainicjuj bibliotek� GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolor�w (podw�jne buforowanie) i bufor kolor�w

	glutInitWindowPosition(windowXPosition, windowYPosition); //Wska� pocz�tkow� pozycj� okna
	glutInitWindowSize(windowWidth, windowHeight); //Wska� pocz�tkowy rozmiar okna
	glutCreateWindow(windowCaption.c_str()); //Utw�rz okno i nadaj mu tytu�	
}


//Procedura inicjuj�ca bibliotek� glew
void OpenGLHelper::initGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		exit(1);
	}

}

void OpenGLHelper::registerWindowResizeProcedure(void(*callback)(int, int))
{
	glutReshapeFunc(callback); //Zarejestruj procedur� changeSize jako procedur� obs�uguj�ca zmian� rozmiaru okna
}

void OpenGLHelper::registerDisplayFrameProcedure(void(*callback)(void))
{
	glutDisplayFunc(callback); //Zarejestruj procedur� displayFrame jako procedur� obs�uguj�ca od�wierzanie okna
}

void OpenGLHelper::registerAnimationProcedure(void(*callback)(void))
{
	glutIdleFunc(callback); //Zarejestruj procedur� nextFrame jako procedur� wywo�ywan� najcz�ci�j jak si� da (animacja)
}

void OpenGLHelper::changeOpenGLWindowDimensions(int width, int height)
{
	glViewport(0, 0, width, height);
}

