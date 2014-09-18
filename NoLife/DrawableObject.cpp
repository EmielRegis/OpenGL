#include "DrawableObject.h"



DrawableObject::DrawableObject(ShaderProgram *shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->mode = DRAWABLE_3D_PRIMITIVE_CUBE;

	loadObject("cube1.obj", suzanne_vertices, suzanne_normals, suzanne_textures, suzanne_colors);
	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	colors = &suzanne_colors[0];
	vertexCount = suzanne_vertices.size() / 4;
	
	this->setupVBO();
	this->setupVAO();
}

DrawableObject::DrawableObject(ShaderProgram *shaderProgram, const char *filepath)
{
	this->shaderProgram = shaderProgram;
	this->mode = DRAWABLE_3D_NOT_TEXTURED_MODEL;

	loadObject(filepath, suzanne_vertices, suzanne_normals, suzanne_textures, suzanne_colors);
	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	colors = &suzanne_colors[0];
	vertexCount = suzanne_vertices.size() / 4;
	
	this->setupVBO();
	this->setupVAO();
}

DrawableObject::DrawableObject(ShaderProgram *shaderProgram, const char * filepath, const char *texturepath)
{
	this->shaderProgram = shaderProgram;
	this->mode = DRAWABLE_3D_SINGLE_TEXTURED_MODEL;
	
	loadObjectWithTextures(filepath, suzanne_vertices, suzanne_normals, suzanne_textures, suzanne_colors);
	this->tex0 = this->loadTexture(texturepath);

	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	colors = &suzanne_colors[0];
	textures = &suzanne_textures[0];
	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();	
}

DrawableObject::DrawableObject(ShaderProgram *shaderProgram, const char *filepath, unsigned int texturesNumber, ...)
{
	this->shaderProgram = shaderProgram;
	this->mode = DRAWABLE_3D_MULTI_TEXTURED_MODEL;

	va_list arguments;                     

	va_start(arguments, texturesNumber);           
	for (int x = 0; x < texturesNumber; x++)
	{
		cout << va_arg(arguments, const char *) << endl;
	}		
	va_end(arguments);                  


	loadObject(filepath, suzanne_vertices, suzanne_normals, suzanne_textures, suzanne_colors);

	//loadObjectWithTextures(filepath, suzanne_vertices, suzanne_normals, suzanne_textures, suzanne_colors);
	//this->tex0 = this->loadTexture(texturepath);

	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	colors = &suzanne_colors[0];
	//textures = &suzanne_textures[0];
	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();
}


DrawableObject::~DrawableObject()
{
	this->freeVAO();
	this->freeVBO();
}

void DrawableObject::changeColor(float r, float g, float b)
{
	for (int i = 0; i < suzanne_colors.size(); i += 4)
	{
		suzanne_colors[i] = r;
		suzanne_colors[i+1] = g;
		suzanne_colors[i+2] = b;
	}

	colors = &suzanne_colors[0];

	this->setupVBO();
	this->setupVAO();
}

void DrawableObject::changeColor(float r, float g, float b, float a)
{
	for (int i = 0; i < suzanne_colors.size(); i += 4)
	{
		suzanne_colors[i] = r;
		suzanne_colors[i + 1] = g;
		suzanne_colors[i + 2] = b;
		suzanne_colors[i + 3] = a;
	}

	colors = &suzanne_colors[0];

	this->setupVBO();
	this->setupVAO();
}


void DrawableObject::setTransparency(float transparency)
{
	for (int i = 0; i < suzanne_colors.size(); i += 4)
	{
		suzanne_colors[i+3] = transparency;
	}

	colors = &suzanne_colors[0];

	this->setupVBO();
	this->setupVAO();
}


GLuint DrawableObject::loadTexture(const char *filepath)
{
	GLuint tex = 0;
	char *filename = (char*)filepath;
	TGAImg img;

	glActiveTexture(GL_TEXTURE0);


	if (img.Load(filename) == IMG_OK)
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		if (img.GetBPP() == 24)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetImg());
		}
		else if (img.GetBPP() == 32)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.GetImg());
		}
		else
		{
			cout << "File format not supported..." << filename << endl;
		}
	}
	else
	{
		cout << "File loading error..." << filename << endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return tex;
}

//³adowanie modelu z Blendera
void DrawableObject::loadObject(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float>&colors) {
	vector<int> elements;
	vector<glm::vec4> verts;
	vector<glm::vec2> text;
	ifstream in(filename, ios::in);

	if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }

	string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {

			istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
			verts.push_back(v);
		}
		else if (line.substr(0, 3) == "vt ")
		{
			istringstream s(line.substr(2));
			glm::vec2 vt; s >> vt.x; s >> vt.y;
			text.push_back(vt);
		}
		else if (line.substr(0, 2) == "f ") {
			istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		else if (line[0] == '#') {  }
		else {  }
	}
	
	for (int i = 0; i < elements.size(); i++)
	{
		vertices.push_back((float)verts[elements[i]].x);
		vertices.push_back((float)verts[elements[i]].y);
		vertices.push_back((float)verts[elements[i]].z);
		vertices.push_back((float)verts[elements[i]].w);

		colors.push_back(1.0f);
		colors.push_back(1.0f);
		colors.push_back(1.0f);
		colors.push_back(1.0f);

		if (text.size() >= verts.size())
		{
			textures.push_back((float)text[elements[i]].x);
			textures.push_back((float)text[elements[i]].y);
		}


		if (i % 3 == 0)
		{
			glm::vec4 a = verts[elements[i + 1]] - verts[elements[i]];
			glm::vec4 b = verts[elements[i + 2]] - verts[elements[i]];

			glm::vec4 n = glm::vec4(glm::normalize(glm::cross(glm::vec3(a.x, a.y, a.z), glm::vec3(b.x, b.y, b.z))), 0.0f);

			for (int j = 0; j < 3; j++)
			{
				normals.push_back(n.x);
				normals.push_back(n.y);
				normals.push_back(n.z);
				normals.push_back(n.w);
			}
		}
	}
}


//³adowanie modelu z Blendera
void DrawableObject::loadObjectWithTextures(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures, vector<float>&colors) {
	vector<int> elements;
	vector<int> elements2;
	vector<glm::vec4> verts;
	vector<glm::vec2> text;
	ifstream in(filename, ios::in);

	if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }

	string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {

			istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
			verts.push_back(v);
		}
		else if (line.substr(0, 3) == "vt ")
		{
			istringstream s(line.substr(3));

			glm::vec2 vt; 
			s >> vt.x; s >> vt.y;
			text.push_back(vt);
		}
		else if (line.substr(0, 2) == "f ") {
			istringstream s(line.substr(2));

			string pars[3];
			s >> pars[0]; s >> pars[1]; s >> pars[2];

			int a, b, c, d, e, f;

			sscanf_s(pars[0].c_str(), "%d/%d", &a, &d);
			sscanf_s(pars[1].c_str(), "%d/%d", &b, &e);
			sscanf_s(pars[2].c_str(), "%d/%d", &c, &f);
	
			a--; b--; c--; d--; e--; f--;

			elements.push_back(a); elements.push_back(b); elements.push_back(c);
			elements2.push_back(d); elements2.push_back(e); elements2.push_back(f);
		}
		else if (line[0] == '#') {}
		else {}
	}

	for (int i = 0; i < elements2.size(); i++)
	{
		textures.push_back((float)text[elements2[i]].x);
		textures.push_back((float)text[elements2[i]].y);
	}

	for (int i = 0; i < elements.size(); i++)
	{
		vertices.push_back((float)verts[elements[i]].x);
		vertices.push_back((float)verts[elements[i]].y);
		vertices.push_back((float)verts[elements[i]].z);
		vertices.push_back((float)verts[elements[i]].w);

		colors.push_back(1.0f);
		colors.push_back(1.0f);
		colors.push_back(1.0f);
		colors.push_back(1.0f);

		if (i % 3 == 0)
		{
			glm::vec4 a = verts[elements[i + 1]] - verts[elements[i]];
			glm::vec4 b = verts[elements[i + 2]] - verts[elements[i]];

			glm::vec4 n = glm::vec4(glm::normalize(glm::cross(glm::vec3(a.x, a.y, a.z), glm::vec3(b.x, b.y, b.z))), 0.0f);

			for (int j = 0; j < 3; j++)
			{
				normals.push_back(n.x);
				normals.push_back(n.y);
				normals.push_back(n.z);
				normals.push_back(n.w);
			}
		}
	}
}


//Procedura rysuj¹ca jakiœ obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
void DrawableObject::draw() {

	if (this->alternateDrawing)
	{	
		glm::mat4 RX = scene.matM = glm::rotate(glm::mat4(1.0f), this->xAngle, glm::vec3(1.0, 1.0, 0.0));
		glm::mat4 RY = scene.matM = glm::rotate(glm::mat4(1.0f), this->yAngle, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 RZ = scene.matM = glm::rotate(glm::mat4(1.0f), this->zAngle, glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(this->xScale, this->zScale, this->yScale));

		glm::mat4 TRAZ = glm::translate(glm::mat4(1.0f), glm::vec3(this->xRotCoord, this->zRotCoord, this->yRotCoord));
		glm::mat4 RAZ = glm::rotate(glm::mat4(1.0f), this->zAngleAround, glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(this->xPosition, this->zPosition, this->yPosition));

		scene.matM = T*RAZ*TRAZ*S*RZ*RY*RX;
	}

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(scene.matP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(scene.matV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(scene.matM));

	glUniform4f(shaderProgram->getUniformLocation("lpos"), 0,2,5,1);

	glUniform1i(shaderProgram->getUniformLocation("textureMap0"), 0);

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

	if (this->mode == DRAWABLE_3D_SINGLE_TEXTURED_MODEL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex0);

	}
	else if (this->mode == DRAWABLE_3D_MULTI_TEXTURED_MODEL)
	{

	}


	//Narysowanie obiektu
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
}


// Natychmiastowa zmiana pozycje
void DrawableObject::instantMove(float xPosition, float yPosition, float zPosition)
{
	this->xPosition += xPosition;
	this->yPosition += yPosition;
	this->zPosition += zPosition;
}

void DrawableObject::move(float xPosition, float yPosition, float zPosition, int speedInMilis)
{
	;
}

void DrawableObject::instantRotate(float xAngle, float yAngle, float zAngle)
{
	this->xAngle += xAngle;
	this->yAngle += yAngle;
	this->zAngle += zAngle;
}

void DrawableObject::rotate(float xAngle, float yAngle, float zAngle, int speedInMilis)
{
	;
}

void DrawableObject::instantRotateAroundPoint(float xAngle, float yAngle, float zAngle, float xRadiusVectorCoord, float yRadiusVectorCoord, float zRadiusVectorCoord)
{
	this->xAngleAround += xAngle;
	this->yAngleAround += yAngle;
	this->zAngleAround += zAngle;

	this->xRotCoord = xRadiusVectorCoord;
	this->yRotCoord = yRadiusVectorCoord;
	this->zRotCoord = zRadiusVectorCoord;
}

void rotateAroundPoint(float xAngle, float yAngle, float zAngle, float xRadiusVectorCoord, float yRadiusVectorCoord, float zRadiusVectorCoord, int timieInMilis)
{
	;
}

void DrawableObject::instantScale(float xScale, float yScale, float zScale)
{
	this->xScale *= xScale;
	this->yScale *= yScale;
	this->zScale *= zScale;
}

void DrawableObject::scale(float xScale, float yScale, float zScale, int speedInMilis)
{
	;
}

void DrawableObject::setAlternativeDrawing(bool alternativeDrawing)
{
	this->alternateDrawing = alternativeDrawing;
}

void DrawableObject::instantScaleNatural(float scalingValue)
{
	this->xScale *= scalingValue;
	this->yScale *= scalingValue;
	this->zScale *= scalingValue;
}

void DrawableObject::scaleNatural(float value, int timeInMilis)
{
	;
}

float DrawableObject::getXCoordinate()
{
	return this->xPosition;
}

float DrawableObject::getYCoordinate()
{
	return this->yPosition;
}

float DrawableObject::getZCoordinate()
{
	return this->zPosition;
}

float DrawableObject::getXRotationAngle()
{
	return this->xAngle;
}

float DrawableObject::getYRotationAngle()
{
	return this->yAngle;
}

float DrawableObject::getZRotationAngle()
{
	return this->zAngle;
}

float DrawableObject::getZRotationAroundAngle()
{
	return this->zAngleAround;
}




GLuint DrawableObject::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który bêdzie zawiera³ tablicê danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicê do VBO

	return handle;
}


//Procedura tworz¹ca bufory VBO zawieraj¹ce dane z tablic opisuj¹cych rysowany obiekt.
void DrawableObject::setupVBO() {
	bufVertices = makeBuffer(vertices, vertexCount, sizeof(float)* 4); //Wspó³rzêdne wierzcho³ków
	bufColors = makeBuffer(colors, vertexCount, sizeof(float)* 4);//Kolory wierzcho³ków
	bufNormals = makeBuffer(normals, vertexCount, sizeof(float)* 4);//Wektory normalne wierzcho³ków

	if (this->mode == DRAWABLE_3D_SINGLE_TEXTURED_MODEL)
	{
		this->bufTextures = makeBuffer(this->textures, this->vertexCount, sizeof(float)* 2);
	}
	else if (this->mode == DRAWABLE_3D_MULTI_TEXTURED_MODEL)
	{

	}
}


void DrawableObject::assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}


//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
void DrawableObject::setupVAO() {
	//Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej
	glGenVertexArrays(1, &vao);

	//Uaktywnij nowo utworzony VAO
	glBindVertexArray(vao);

	assignVBOtoAttribute("vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute("color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
	assignVBOtoAttribute("normal", bufNormals, 4); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze

	if (this->mode == DRAWABLE_3D_SINGLE_TEXTURED_MODEL)
	{
		assignVBOtoAttribute("texCoord", bufTextures, 2);
	}
	else if (this->mode == DRAWABLE_3D_MULTI_TEXTURED_MODEL)
	{

	}

	glBindVertexArray(0);
}

void DrawableObject::freeVBO() {
	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufColors);
	glDeleteBuffers(1, &bufNormals);

	if (this->mode == DRAWABLE_3D_SINGLE_TEXTURED_MODEL)
	{
		glDeleteBuffers(1, &bufTextures);
	}
	else if (this->mode == DRAWABLE_3D_MULTI_TEXTURED_MODEL)
	{

	}
}


void DrawableObject::freeVAO() {
	glDeleteVertexArrays(1, &vao);
}
