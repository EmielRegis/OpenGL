#include "DrawableObject2D.h"



DrawableObject2D::DrawableObject2D(ShaderProgram *shaderProgram, MODE mode)
{
	this->shaderProgram = shaderProgram;

	this->mode = mode;
	
	if (mode == DRAWABLE_TRIANGLE)
	{
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(0.0f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);
	}
	else if (mode == DRAWABLE_SQUARE)
	{
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);
	}
	else if (mode == DRAWABLE_CIRCLE)
	{
		for (int i = 0; i < 360; i++)
		{
			float r = 1.0;
			float a1 = r * cos(i);
			float b1 = r* sin(i);
			float a2 = r * cos(i+1);
			float b2 = r * sin(i+1);

			suzanne_vertices.push_back(a1);
			suzanne_vertices.push_back(b1);
			suzanne_vertices.push_back(-1.0f);
			suzanne_vertices.push_back(1.0f);

			suzanne_vertices.push_back(a2);
			suzanne_vertices.push_back(b2);
			suzanne_vertices.push_back(-1.0f);
			suzanne_vertices.push_back(1.0f);

			suzanne_vertices.push_back(0.0);
			suzanne_vertices.push_back(0.0);
			suzanne_vertices.push_back(-1.0f);
			suzanne_vertices.push_back(1.0f);

			suzanne_colors.push_back(0.8f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(1.0f);

			suzanne_colors.push_back(0.8f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(1.0f);

			suzanne_colors.push_back(0.2f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(0.0f);
			suzanne_colors.push_back(1.0f);
		}
		
	}
	else if (mode == DRAWABLE_LINE)
	{
		suzanne_vertices.push_back(-0.01f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(0.01f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(0.01f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(0.01f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(-0.01f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_vertices.push_back(-0.01f);
		suzanne_vertices.push_back(1.0f);
		suzanne_vertices.push_back(-1.0f);
		suzanne_vertices.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.8f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);

		suzanne_colors.push_back(0.2f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(0.0f);
		suzanne_colors.push_back(1.0f);
	}


	vertices = &suzanne_vertices[0];
	colors = &suzanne_colors[0];

	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();

}


DrawableObject2D::DrawableObject2D(ShaderProgram *shaderProgram, const char *filepath)
{
	this->shaderProgram = shaderProgram;

	this->mode = DRAWABLE_2D_MODEL;

	loadObject(filepath, suzanne_vertices, suzanne_textures, suzanne_colors);
	vertices = &suzanne_vertices[0];
	colors = &suzanne_colors[0];
	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();
}

DrawableObject2D::DrawableObject2D(ShaderProgram *shaderProgram, const char * filepath, const char *texturepath)
{
	this->isTexurable = true;

	this->shaderProgram = shaderProgram;

	this->mode = DRAWABLE_2D_MODEL_WITH_TEXTURES;

	loadObjectWithTextures(filepath, suzanne_vertices, suzanne_textures, suzanne_colors);
	this->tex0 = this->loadTexture(texturepath);

	vertices = &suzanne_vertices[0];
	colors = &suzanne_colors[0];
	textures = &suzanne_textures[0];

	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();
}


DrawableObject2D::~DrawableObject2D()
{
	this->freeVAO();
	this->freeVBO();
}

//Procedura rysuj¹ca jakiœ obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
void DrawableObject2D::drawObject()
{
	glm::mat4 S = glm::scale(glm::mat4(1.0), glm::vec3(this->xScale, this->yScale, 1));
	glm::mat4 T = glm::translate(glm::mat4(1.0), glm::vec3(this->xPosition, this->yPosition, 0));
	glm::mat4 R = glm::rotate(glm::mat4(1.0), this->angle, glm::vec3(0.0, 0.0, 1.0));

	scene.matM = T*S*R;
	

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(scene.matP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(scene.matM));

	//glUniform1i(shaderProgram->getUniformLocation("textureMap0"), 0);

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

	if (isTexurable)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex0);
	}

	//Narysowanie obiektu
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
}


void DrawableObject2D::changeColor(float r, float g, float b)
{
	for (int i = 0; i < suzanne_colors.size(); i += 4)
	{
		suzanne_colors[i] = r;
		suzanne_colors[i + 1] = g;
		suzanne_colors[i + 2] = b;
		suzanne_colors[i + 3] = 1.0f;
	}

	colors = &suzanne_colors[0];

	this->setupVBO();
	this->setupVAO();
}

void DrawableObject2D::changeColor(float r, float g, float b, float a)
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

void DrawableObject2D::addTexture(const char *filepath)
{
	this->loadTexture(filepath);
	this->isTexurable = true;
}


GLuint DrawableObject2D::loadTexture(const char *filepath)
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
void DrawableObject2D::loadObject(const char* filename, vector<float> &vertices, vector<float> &textures, vector<float>&colors) {
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
		else if (line[0] == '#') {}
		else {}
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
		}
	}
}


//³adowanie modelu z Blendera
void DrawableObject2D::loadObjectWithTextures(const char* filename, vector<float> &vertices, vector<float> &textures, vector<float>&colors) {
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
		}
	}
}



// Natychmiastowa zmiana pozycje
void DrawableObject2D::instantMove(float xPosition, float yPosition)
{
	this->xPosition += xPosition;
	this->yPosition += yPosition;
}

void DrawableObject2D::move(float xPosition, float yPosition, int speedInMilis)
{
	;
}

void DrawableObject2D::instantRotate(float angle)
{
	this->angle += angle;
}

void DrawableObject2D::rotate(float angle, int speedInMilis)
{
	;
}

void DrawableObject2D::instantScale(float xScale, float yScale)
{
	this->xScale *= xScale;
	this->yScale *= yScale;
}

void DrawableObject2D::scale(float xScale, float yScale, int speedInMilis)
{
	;
}

void DrawableObject2D::instantScaleNatural(float scalingValue)
{
	this->xScale *= scalingValue;
	this->yScale *= scalingValue;
}

void DrawableObject2D::scaleNatural(float value, int timeInMilis)
{
	;
}

GLuint DrawableObject2D::makeBuffer(void *data, int vertexCount, int vertexSize) {
	GLuint handle;

	glGenBuffers(1, &handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który bêdzie zawiera³ tablicê danych
	glBindBuffer(GL_ARRAY_BUFFER, handle);  //Uaktywnij wygenerowany uchwyt VBO 
	glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicê do VBO

	return handle;
}


//Procedura tworz¹ca bufory VBO zawieraj¹ce dane z tablic opisuj¹cych rysowany obiekt.
void DrawableObject2D::setupVBO() {
	bufVertices = makeBuffer(vertices, vertexCount, sizeof(float)* 4); //Wspó³rzêdne wierzcho³ków
	bufColors = makeBuffer(colors, vertexCount, sizeof(float)* 4);//Kolory wierzcho³ków

	if (this->isTexurable)
	{
		this->bufTextures = makeBuffer(this->textures, this->vertexCount, sizeof(float)* 2);
	}
}


void DrawableObject2D::assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}


//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
void DrawableObject2D::setupVAO() {
	//Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej
	glGenVertexArrays(1, &vao);

	//Uaktywnij nowo utworzony VAO
	glBindVertexArray(vao);

	assignVBOtoAttribute("vertex", bufVertices, 4); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	assignVBOtoAttribute("color", bufColors, 4); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze

	if (this->isTexurable)
	{
		assignVBOtoAttribute("texCoord", bufTextures, 2);
	}

	glBindVertexArray(0);
}


void DrawableObject2D::freeVBO() {
	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufColors);
}


void DrawableObject2D::freeVAO() {
	glDeleteVertexArrays(1, &vao);
}
