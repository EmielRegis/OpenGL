#pragma once

#include "libraries/glm/gtc/type_ptr.hpp"
#include "libraries/shaderprogram/shaderprogram.h"

class Scene
{
public:
	static Scene& getInstance();

	void initScene();

	bool isInitialized(void);

	//Uchwyty na shadery
	ShaderProgram *shaderProgram; //Wskaünik na obiekt reprezentujπcy program cieniujπcy.
	ShaderProgram *shaderProgram2D; //Wskaünik na obiekt reprezentujπcy program cieniujπcy w przestrzeni 2D - interfejs uøytkownika.
	ShaderProgram *shaderProgramPro;
	ShaderProgram *shaderProgramProTex;
	ShaderProgram *shaderProgramEyePerspective;

	//ShaderProgram *shaderProgram; //Wskaünik na obiekt reprezentujπcy program cieniujπcy.

	glm::mat4  matP;//rzutowania
	glm::mat4  matV;//widoku
	glm::mat4  matM;//modelu


protected:
	static Scene scene;

	bool initialized = false;

	Scene();

	Scene(Scene const&);
	void operator=(Scene const&);

	
	void setupShaders();
	void cleanShaders();

};

