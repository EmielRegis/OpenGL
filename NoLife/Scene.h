#pragma once

#include "glm/gtc/type_ptr.hpp"
#include "shaderprogram.h"

class Scene
{
public:
	static Scene& getInstance();

	void initScene();

	bool isInitialized(void);

	//Uchwyty na shadery
	ShaderProgram *shaderProgram; //Wska�nik na obiekt reprezentuj�cy program cieniuj�cy.
	ShaderProgram *shaderProgram2D; //Wska�nik na obiekt reprezentuj�cy program cieniuj�cy w przestrzeni 2D - interfejs u�ytkownika.
	ShaderProgram *shaderProgramPro;
	ShaderProgram *shaderProgramProTex;

	//ShaderProgram *shaderProgram; //Wska�nik na obiekt reprezentuj�cy program cieniuj�cy.

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

