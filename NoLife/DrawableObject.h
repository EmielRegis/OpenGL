#pragma once

#include "libraries/gl/glew.h"
#include "libraries/gl/freeglut.h"
#include "libraries/glm/glm.hpp"
#include "libraries/glm/gtc/matrix_transform.hpp"
#include "libraries/glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "libraries/tga/tga.h"
#include "libraries/shaderprogram/shaderprogram.h"
#include <cstdarg>
#include "vector"
#include <ios>
#include <sstream>
#include "Scene.h"
#include "Drawable.h"



using namespace std;


class DrawableObject : public Drawable
{
public:
	static enum MODE
	{
		DRAWABLE_3D_PRIMITIVE_CUBE,
		DRAWABLE_3D_PRIMITIVE_BALL,
		DRAWABLE_3D_NOT_TEXTURED_MODEL,
		DRAWABLE_3D_SINGLE_TEXTURED_MODEL,
		DRAWABLE_3D_MULTI_TEXTURED_MODEL,
	};

	DrawableObject(ShaderProgram *shaderProgram);
	DrawableObject(ShaderProgram *shaderProgram, const char * filepath);
	DrawableObject(ShaderProgram *shaderProgram, const char * filepath, const char *texturepath);
	DrawableObject(ShaderProgram *shaderProgram, const char *filepath, unsigned int texturesNumber, ...);
	~DrawableObject();

	

	// Zmiana koloru modelu
	void changeColor(float r, float g, float b);

	void changeColor(float r, float g, float b, float a);

	// Ustawienie przezroczystosci modelu
	void setTransparency(float transparency);

	//Procedura rysuj¹ca model. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
	void draw();

	// Natychmiastowa zmiana pozycje
	void instantMove(float xPosition, float yPosition, float zPosition);
	
	void move(float xPosition, float yPosition, float zPosition, int timeInMilis);

	void instantRotate(float xAngle, float yAngle, float zAngle);

	void rotate(float xAngle, float yAngle, float zAngle, int timeInMilis);

	void instantRotateAroundPoint(float xAngle, float yAngle, float zAngle, float xRadiusVectorCoord, float yRadiusVectorCoord, float zRadiusVectorCoord);

	void rotateAroundPoint(float xAngle, float yAngle, float zAngle, float xRadiusVectorCoord, float yRadiusVectorCoord, float zRadiusVectorCoord, int timeInMilis);

	void instantScale(float xScale, float yScale, float zScale);

	void scale(float xScale, float yScale, float zScale, int timeInMilis);

	void instantScaleNatural(float scalingValue);

	void scaleNatural(float value, int timeInMilis);

	void setAlternativeDrawing(bool alternativeDrawing);

	float getXCoordinate();

	float getYCoordinate();

	float getZCoordinate();

	float getXRotationAngle();

	float getYRotationAngle();

	float getZRotationAngle();

	float getZRotationAroundAngle();


protected:
	Scene &scene  = Scene::getInstance();

	float xPosition = 0, yPosition = 0, zPosition = 0, xAngle = 0, yAngle = 0, zAngle = 0, xAngleAround = 0, yAngleAround = 0, zAngleAround = 0, xRotCoord = 0, yRotCoord = 0, zRotCoord = 0, xScale = 1, yScale = 1, zScale = 1;
	
	unsigned mode;
	bool alternateDrawing = false;

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

	unsigned int texturesCount;
	GLuint tex0;
	bool isTexurable = false;

	
	//Ladowanie modelu w formacie .obj bez tekstur
	void loadObject(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	//Ladowanie modelu w formacie .obj wraz z teksturami
	void loadObjectWithTextures(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float> &colors);

	//Ladowanie tekstur dla modelu
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

