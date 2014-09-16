#pragma once
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "tga/tga.h"
#include "shaderprogram.h"


static class OpenGLHelper
{
public:
	static void initOpenGL(int *argc, char** argv, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight);
	static void registerWindowResizeProcedure(void(*callback)(int, int));
	static void registerDisplayFrameProcedure(void(*callback)(void));
	static void registerAnimationProcedure(void(*callback)(void));
private:
	OpenGLHelper();
	~OpenGLHelper();
	static void initGLUT(int *argc, char** argv, int windowXPosition, int windowYPosition, int windowWidth, int windowHeight);
	static void initGLEW();
};

