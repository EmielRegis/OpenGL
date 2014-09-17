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
	shaderProgram = new ShaderProgram("resources/shaders/vshader.txt", NULL, "resources/shaders/fshader.txt");
	shaderProgram2D = new ShaderProgram("resources/shaders/vshader2D.txt", NULL, "resources/shaders/fshader2D.txt");
	shaderProgramPro = new ShaderProgram("resources/shaders/vshaderPro.txt", NULL, "resources/shaders/fshaderPro.txt");
	shaderProgramProTex = new ShaderProgram("resources/shaders/vshaderProTex.txt", NULL, "resources/shaders/fshaderProTex.txt");
	shaderProgramEyePerspective = new ShaderProgram("resources/shaders/vshaderEye.txt", NULL, "resources/shaders/fshaderEye.txt");
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
