#include "DrawableObject.h"



DrawableObject::DrawableObject(ShaderProgram *shaderProgram)
{
	this->shaderProgram = shaderProgram;

	load_obj("cube1.obj", suzanne_vertices, suzanne_normals, suzanne_textures);
	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	//colors = &suzanne_colors[0]
	//textures = &suzanne_textures[0];
	//elements = &suzanne_elements[0];
	vertexCount = suzanne_vertices.size() / 4;

	this->setupVBO();
	this->setupVAO();
}


DrawableObject::DrawableObject(ShaderProgram *shaderProgram, const char *filepath)
{
	this->shaderProgram = shaderProgram;

	load_obj(filepath, suzanne_vertices, suzanne_normals, suzanne_textures);
	vertices = &suzanne_vertices[0];
	normals = &suzanne_normals[0];
	//colors = &suzanne_colors[0]
	//textures = &suzanne_textures[0];
	//elements = &suzanne_elements[0];
	vertexCount = suzanne_vertices.size() / 4;
	
	this->setupVBO();
	this->setupVAO();
}


DrawableObject::~DrawableObject()
{
	this->freeVAO();
	this->freeVBO();
}


//³adowanie modelu z Blendera
void DrawableObject::load_obj(const char* filename, vector<float> &vertices, vector<float> &normals, vector<float> &textures) {
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
	//cout << elements.size() << endl << endl;
}


//Procedura rysuj¹ca jakiœ obiekt. Ustawia odpowiednie parametry dla vertex shadera i rysuje.
void DrawableObject::drawObject() {
	//W³¹czenie programu cieniuj¹cego, który ma zostaæ u¿yty do rysowania
	//W tym programie wystarczy³oby wywo³aæ to raz, w setupShaders, ale chodzi o pokazanie, 
	//¿e mozna zmieniaæ program cieniuj¹cy podczas rysowania jednej sceny
	shaderProgram->use();

	//Przeka¿ do shadera macierze P,V i M.
	//W linijkach poni¿ej, polecenie:
	//  shaderProgram->getUniformLocation("P") 
	//pobiera numer slotu odpowiadaj¹cego zmiennej jednorodnej o podanej nazwie
	//UWAGA! "P" w powy¿szym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze, 
	//a matP w glm::value_ptr(matP) odpowiada deklaracji  "glm::mat4 matP;" TYM pliku.
	//Ca³a poni¿sza linijka przekazuje do zmiennej jednorodnej P w vertex shaderze dane ze zmiennej matP
	//zadeklarowanej globalnie w tym pliku. 
	//Pozosta³e polecenia dzia³aj¹ podobnie.
	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, glm::value_ptr(scene.matP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, glm::value_ptr(scene.matV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(scene.matM));

	//Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powi¹zañ slotów atrybutów z tablicami z danymi
	glBindVertexArray(vao);

	//Narysowanie obiektu
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Posprz¹tanie po sobie (niekonieczne w sumie je¿eli korzystamy z VAO dla ka¿dego rysowanego obiektu)
	glBindVertexArray(0);
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

	glBindVertexArray(0);
}



/*void initOpenGL() {
	setupShaders();
	setupVBO();
	setupVAO();

}*/





void DrawableObject::freeVBO() {
	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufColors);
	glDeleteBuffers(1, &bufNormals);
}


void DrawableObject::freeVAO() {
	glDeleteVertexArrays(1, &vao);
}





	

	//initOpenGL();
	 

	// ...

	//cleanShaders();



