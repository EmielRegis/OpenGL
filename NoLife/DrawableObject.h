#pragma once

#include "gl/glew.h"
#include "gl/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "tga.h"
#include "shaderprogram.h"

#include "vector"
#include <ios>
#include <sstream>
#include "Scene.h"



using namespace std;


class DrawableObject
{
public:
	DrawableObject(ShaderProgram *shaderProgram);
	DrawableObject(ShaderProgram *shaderProgram, const char * filepath);
	DrawableObject(ShaderProgram *shaderProgram, const char * filepath, const char *texturepath);
	~DrawableObject();

	//�adowanie modelu z Blendera
	void load_obj(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	void load_obj_with_textures(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	void changeColor(float r, float g, float b);

	//Procedura rysuj�ca jaki� obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
	void drawObject();


protected:
	Scene &scene  = Scene::getInstance();

	ShaderProgram *shaderProgram;

	//Uchwyty na VAO i bufory wierzcho�k�w
	GLuint vao;
	GLuint bufVertices; //Uchwyt na bufor VBO przechowuj�cy tablic� wsp�rz�dnych wierzcho�k�w
	GLuint bufColors;  //Uchwyt na bufor VBO przechowuj�cy tablic� kolor�w
	GLuint bufNormals; //Uchwyt na bufor VBO przechowuj�cy tablic� wektor�w normalnych
	GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablic� warto�ci tekstur
	GLuint bufElements; //Uchwyt na bufor VBO elementow - trojkatow o ile takowy bufor mozna utworzyc

	float *vertices;
	float *colors;
	float *normals;
	float *textures;
	GLushort *elements;
	int vertexCount;

	vector<float> suzanne_vertices;
	vector<float> suzanne_normals;
	vector<float> suzanne_colors;
	vector<float> suzanne_textures;
	vector<GLushort> suzanne_elements;

	GLuint tex0;
	bool isTexurable = false;

	
	GLuint loadTexture(const char *filepath);

	//Tworzy bufor na wierzcho�ki, kolory i normalne
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);

	//Procedura tworz�ca bufory VBO zawieraj�ce dane z tablic opisuj�cych rysowany obiekt.
	void setupVBO();

	//Przypisanie VBO do atrybut�w
	void assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize);

	//Procedura tworz�ca VAO - "obiekt" OpenGL wi���cy numery slot�w atrybut�w z buforami VBO
	void setupVAO();

	//Uwolnij zasoby przypisane do VBO
	void freeVBO();

	//Uwolnij zasoby przypisane do VAO
	void freeVAO();
};

