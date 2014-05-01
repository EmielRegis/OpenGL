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
