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

//Procedura inicjuj¹ca biblotekê glut
void OpenGLHelper::initGLUT(int *argc, char** argv, string windowCaption, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight) {
	glutInit(argc, argv); //Zainicjuj bibliotekê GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Alokuj bufory kolorów (podwójne buforowanie) i bufor kolorów

	glutInitWindowPosition(windowXPosition, windowYPosition); //Wska¿ pocz¹tkow¹ pozycjê okna
	glutInitWindowSize(windowWidth, windowHeight); //Wska¿ pocz¹tkowy rozmiar okna
	glutCreateWindow(windowCaption.c_str()); //Utwórz okno i nadaj mu tytu³	
}


//Procedura inicjuj¹ca bibliotekê glew
void OpenGLHelper::initGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		exit(1);
	}

}

void OpenGLHelper::registerWindowResizeProcedure(void(*callback)(int, int))
{
	glutReshapeFunc(callback); //Zarejestruj procedurê changeSize jako procedurê obs³uguj¹ca zmianê rozmiaru okna
}

void OpenGLHelper::registerDisplayFrameProcedure(void(*callback)(void))
{
	glutDisplayFunc(callback); //Zarejestruj procedurê displayFrame jako procedurê obs³uguj¹ca odœwierzanie okna
}

void OpenGLHelper::registerAnimationProcedure(void(*callback)(void))
{
	glutIdleFunc(callback); //Zarejestruj procedurê nextFrame jako procedurê wywo³ywan¹ najczêœciêj jak siê da (animacja)
}

void OpenGLHelper::changeOpenGLWindowDimensions(int width, int height)
{
	glViewport(0, 0, width, height);
}

