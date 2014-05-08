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

	//³adowanie modelu z Blendera
	void load_obj(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	void load_obj_with_textures(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	void changeColor(float r, float g, float b);

	//Procedura rysuj¹ca jakiœ obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
	void drawObject();


protected:
	Scene &scene  = Scene::getInstance();

	ShaderProgram *shaderProgram;

	//Uchwyty na VAO i bufory wierzcho³ków
	GLuint vao;
	GLuint bufVertices; //Uchwyt na bufor VBO przechowuj¹cy tablicê wspó³rzêdnych wierzcho³ków
	GLuint bufColors;  //Uchwyt na bufor VBO przechowuj¹cy tablicê kolorów
	GLuint bufNormals; //Uchwyt na bufor VBO przechowuj¹cy tablicê wektorów normalnych
	GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablicê wartoœci tekstur
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

	//Tworzy bufor na wierzcho³ki, kolory i normalne
	GLuint makeBuffer(void *data, int vertexCount, int vertexSize);

	//Procedura tworz¹ca bufory VBO zawieraj¹ce dane z tablic opisuj¹cych rysowany obiekt.
	void setupVBO();

	//Przypisanie VBO do atrybutów
	void assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize);

	//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
	void setupVAO();

	//Uwolnij zasoby przypisane do VBO
	void freeVBO();

	//Uwolnij zasoby przypisane do VAO
	void freeVAO();
};

