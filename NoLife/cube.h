#ifndef CUBE_H
#define CUBE_H

//Model kostki złożonej z trójkątów
//Zawiera tablice:
//cubeVertices - tablica współrzędnych homogenicznych wierzchołków
//cubeNormals - tablica kolorów
//cubeTexCoords - tablica współrzędnych teksturowania
//cubeColors - tablica kolorów
//Culling GL_CW
//TBN friendly

int cubeVertexCount=36;

float cubeVertices[]={
	 -1,1,-1,1,
	 -1,-1,-1,1,
	 -1,-1,1,1,

	 -1,-1,-1,1,
	 1,-1,-1,1,
	 1,-1,1,1,

	 -1,-1,1,1,
	 -1,-1,-1,1,
	 1,-1,1,1

	
}; 

float cubeColors[]={
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,
	
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,
	
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
	
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f,
};

float cubeNormals[]={
	
	-1, 0, 0, 0,
	-1, 0, 0, 0,
	-1, 0, 0, 0,


	0, -1, 0, 0,
	0, -1, 0, 0,
	0, -1, 0, 0,

	0, -1, 0, 0,
	0, -1, 0, 0,
	0, -1, 0, 0,
};

float cubeTexCoords[]={
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
	
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
	
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
	
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
	
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
	
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f, 
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};



#endif