#pragma once
#include "libraries/gl/glew.h"
#include "libraries/gl/freeglut.h"
#include "libraries/glm/glm.hpp"
#include "libraries/glm/gtc/matrix_transform.hpp"
#include "libraries/glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "libraries/tga/tga.h"
#include "libraries/shaderprogram/shaderprogram.h"

using namespace std;

static class OpenGLHelper
{
public:
	static void initOpenGL(int *argc, char** argv, string windowCaption, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight);
	static void registerWindowResizeProcedure(void(*callback)(int, int));
	static void registerDisplayFrameProcedure(void(*callback)(void));
	static void registerAnimationProcedure(void(*callback)(void));
	static void changeOpenGLWindowDimensions(int width, int height);
private:
	OpenGLHelper();
	~OpenGLHelper();
	static void initGLUT(int *argc, char** argv, string windowCaption, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight);
	static void initGLEW();
};

