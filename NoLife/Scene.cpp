#include "Scene.h"


Scene::Scene()
{
	///shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
	//delete shaderProgram;
}

Scene Scene::scene;

Scene &Scene::getInstance()
{
	return Scene::scene;
}

void Scene::setupShaders()
{
	shaderProgram = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
	shaderProgram2D = new ShaderProgram("vshader2D.txt", NULL, "fshader2D.txt");
	shaderProgramPro = new ShaderProgram("vshaderPro.txt", NULL, "fshaderPro.txt");
	shaderProgramProTex = new ShaderProgram("vshaderProTex.txt", NULL, "fshaderProTex.txt");
	shaderProgramEyePerspective = new ShaderProgram("vshaderEye.txt", NULL, "fshaderEye.txt");
}

//Zwolnij pamiêæ karty graficznej z shaderów i programu cieniuj¹cego
void Scene::cleanShaders() 
{
	delete shaderProgram;
	delete shaderProgram2D;
	delete shaderProgramPro;
	delete shaderProgramProTex;
}

void Scene::initScene()
{

	this->setupShaders();
	initialized = true;
}

bool Scene::isInitialized(void)
{
	return this->initialized;
}
