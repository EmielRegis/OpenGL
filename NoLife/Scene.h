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
	ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.
	ShaderProgram *shaderProgram2D; //Wskaźnik na obiekt reprezentujący program cieniujący w przestrzeni 2D - interfejs użytkownika.
	ShaderProgram *shaderProgramPro;
	ShaderProgram *shaderProgramProTex;
	ShaderProgram *shaderProgramEyePerspective;

	//ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.

	glm::mat4  matP;//rzutowania
	glm::mat4  matV;//widoku


protected:
	static Scene scene;

	bool initialized = false;

	Scene();

	Scene(Scene const&);
	void operator=(Scene const&);

	
	void setupShaders();
	void cleanShaders();

};

