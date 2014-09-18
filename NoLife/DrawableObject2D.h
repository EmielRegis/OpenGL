#pragma once

#include "libraries/gl/glew.h"
#include "libraries/gl/freeglut.h"
#include "libraries/glm/glm.hpp"
#include "libraries/glm/gtc/matrix_transform.hpp"
#include "libraries/glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "libraries/tga/tga.h"
#include "libraries/shaderprogram/shaderprogram.h"
#include "Drawable.h"

#include "vector"
#include <ios>
#include <sstream>
#include "Scene.h"



using namespace std;



class DrawableObject2D : public Drawable
{
public:
	static enum MODE
	{
		DRAWABLE_2D_PRIMITIVE_TRIANGLE,
		DRAWABLE_2D_PRIMITIVE_SQUARE,
		DRAWABLE_2D_PRIMITIVE_CIRCLE,
		DRAWABLE_2D_PRIMITIVE_LINE,
		DRAWABLE_2D_NOT_TEXTURED_MODEL,
		DRAWABLE_2D_SINGLE_TEXTURED_MODEL,
		DRAWABLE_2D_MULTI_TEXTURED_MODEL
	};


	DrawableObject2D(ShaderProgram *shaderProgram, MODE mode);
	DrawableObject2D(ShaderProgram *shaderProgram, const char * filepath);
	DrawableObject2D(ShaderProgram *shaderProgram, const char * filepath, const char *texturepath);
	~DrawableObject2D();



	// Zmiana koloru modelu
	void changeColor(float r, float g, float b);

	void changeColor(float r, float g, float b, float a);

	void addTexture(const char *filepath);



	//Procedura rysuj�ca model. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
	void draw();

	// Natychmiastowa zmiana pozycje
	void instantMove(float xPosition, float yPosition);

	void move(float xPosition, float yPosition, int timeInMilis);

	void instantRotate(float angle);

	void rotate(float angle, int timeInMilis);

	void instantScale(float xScale, float yScale);

	void scale(float xScale, float yScale, int timeInMilis);

	void instantScaleNatural(float scalingValue);

	void scaleNatural(float value, int timeInMilis);
	

protected:
	Scene &scene = Scene::getInstance();
	glm::mat4  matM;

	unsigned mode;

	float xPosition = 0, yPosition = 0, angle = 0, xScale = 1, yScale = 1;


	ShaderProgram *shaderProgram;

	//Uchwyty na VAO i bufory wierzcho�k�w
	GLuint vao;
	GLuint bufVertices; //Uchwyt na bufor VBO przechowuj�cy tablic� wsp�rz�dnych wierzcho�k�w
	GLuint bufColors;  //Uchwyt na bufor VBO przechowuj�cy tablic� kolor�w
	GLuint bufTextures; //Uchwyt na bufor VBO przechowujacy tablic� warto�ci tekstur

	float *vertices;
	float *colors;
	float *textures;
	//GLushort *elements;
	int vertexCount;

	vector<float> suzanne_vertices;
	vector<float> suzanne_colors;
	vector<float> suzanne_textures;
	//vector<GLushort> suzanne_elements;

	GLuint tex0;
	bool isTexurable = false;


	//Ladowanie modelu w formacie .obj bez tekstur
	void loadObject(const char* filename, vector<float> &vertices, vector<float> &textures, vector<float> &colors);

	//Ladowanie modelu w formacie .obj wraz z teksturami
	void loadObjectWithTextures(const char* filename, vector<float> &vertices, vector<float> &textures, vector<float> &colors);

	//Ladowanie tekstur dla modelu
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

