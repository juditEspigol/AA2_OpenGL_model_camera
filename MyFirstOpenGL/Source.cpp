#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <sstream>
#include <stb_image.h>

#include "MatrixUtilities.h"
#include "ShaderProgram.h"
#include "ProgramManager.h"
#include "GLManager.h"

#include "GameObject.h"
#include "Camera.h"
#include "Model.h"

std::vector<Model> models;

//Funcion que leera un .obj y devolvera un modelo para poder ser renderizado
Model LoadOBJModel(const std::string& filePath) {

	//Verifico archivo y si no puedo abrirlo cierro aplicativo
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Variables lectura fichero
	std::string line;
	std::stringstream ss;
	std::string prefix;
	glm::vec3 tmpVec3;
	glm::vec2 tmpVec2;

	//Variables elemento modelo
	std::vector<float> vertexs;
	std::vector<float> vertexNormal;
	std::vector<float> textureCoordinates;

	//Variables temporales para algoritmos de sort
	std::vector<float> tmpVertexs;
	std::vector<float> tmpNormals;
	std::vector<float> tmpTextureCoordinates;

	//Recorremos archivo linea por linea
	while (std::getline(file, line)) {

		//Por cada linea reviso el prefijo del archivo que me indica que estoy analizando
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//Estoy leyendo un vertice
		if (prefix == "v") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector de vertices los valores
			tmpVertexs.push_back(tmpVec3.x);
			tmpVertexs.push_back(tmpVec3.y);
			tmpVertexs.push_back(tmpVec3.z);
		}

		//Estoy leyendo una UV (texture coordinate)
		else if (prefix == "vt") {

			//Las UVs son siempre imagenes 2D asi que uso el tmpvec2 para almacenarlas
			ss >> tmpVec2.x >> tmpVec2.y;

			//Almaceno en mi vector temporal las UVs
			tmpTextureCoordinates.push_back(tmpVec2.x);
			tmpTextureCoordinates.push_back(tmpVec2.y);

		}

		//Estoy leyendo una normal
		else if (prefix == "vn") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector temporal de normales las normales
			tmpNormals.push_back(tmpVec3.x);
			tmpNormals.push_back(tmpVec3.y);
			tmpNormals.push_back(tmpVec3.z);

		}

		//Estoy leyendo una cara
		else if (prefix == "f") {

			int vertexData;
			short counter = 0;

			//Obtengo todos los valores hasta un espacio
			while (ss >> vertexData) {

				//En orden cada numero sigue el patron de vertice/uv/normal
				switch (counter) {
				case 0:
					//Si es un vertice lo almaceno - 1 por el offset y almaceno dos seguidos al ser un vec3, salto 1 / y aumento el contador en 1
					vertexs.push_back(tmpVertexs[(vertexData - 1) * 3]);
					vertexs.push_back(tmpVertexs[((vertexData - 1) * 3) + 1]);
					vertexs.push_back(tmpVertexs[((vertexData - 1) * 3) + 2]);
					ss.ignore(1, '/');
					counter++;
					break;
				case 1:
					//Si es un uv lo almaceno - 1 por el offset y almaceno dos seguidos al ser un vec2, salto 1 / y aumento el contador en 1
					textureCoordinates.push_back(tmpTextureCoordinates[(vertexData - 1) * 2]);
					textureCoordinates.push_back(tmpTextureCoordinates[((vertexData - 1) * 2) + 1]);
					ss.ignore(1, '/');
					counter++;
					break;
				case 2:
					//Si es una normal la almaceno - 1 por el offset y almaceno tres seguidos al ser un vec3, salto 1 / y reinicio
					vertexNormal.push_back(tmpNormals[(vertexData - 1) * 3]);
					vertexNormal.push_back(tmpNormals[((vertexData - 1) * 3) + 1]);
					vertexNormal.push_back(tmpNormals[((vertexData - 1) * 3) + 2]);
					counter = 0;
					break;
				}
			}
		}
	}
	return Model(vertexs, textureCoordinates, vertexNormal);
}

void main() {

	//Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	GL_MANAGER.WindowsConfiguration(); 

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	GL_MANAGER.ActivateBackCulling(); 

	//Leer textura
	int width, height, nrChannels;
	unsigned char* textureInfo = stbi_load("Assets/Textures/troll.png", &width, &height, &nrChannels, 0);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) 
	{
		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.6f, 1.f, 1.f);
		//Definimos modo de dibujo para cada cara
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		//Compilar shaders
		ShaderProgram myFirstProgram = ShaderProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "MyFirstFragmentShader.glsl");
		ShaderProgram uwu = ShaderProgram("MyFirstVertexShader.glsl", "MyFirstGeometryShader.glsl", "MyFirstFragmentShader.glsl");
		//Compìlar programa
		PROGRAM_MANAGER.compiledPrograms.push_back(CreateProgram(myFirstProgram));
		PROGRAM_MANAGER.compiledPrograms.push_back(CreateProgram(uwu));

		//Declarar instancia de GameObject
		Camera camera = Camera(PROGRAM_MANAGER.compiledPrograms[0], glm::vec3(0.f, 0.5f, 2.f), 45.0f, 0.1f, 10.f);

		GameObject troll = GameObject(PROGRAM_MANAGER.compiledPrograms[0], 
			glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.5f), { 0.5f, 1.f, 0.5f, 1.f });

		GameObject troll_2 = GameObject(PROGRAM_MANAGER.compiledPrograms[0],
			glm::vec3(-0.5f, 0.f, 0.5f), glm::vec3(0.f, 45.f, 0.f), glm::vec3(0.25f), { 1.f, 0.5f, 0.5f, 1.f });

		GameObject troll_3 = GameObject(PROGRAM_MANAGER.compiledPrograms[0],
			glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.f, 300.f, 0.f), glm::vec3(0.25f), { 0.5f, 0.5f, 1.f, 1.f });

		//Cargo Modelo
		models.push_back(LoadOBJModel("Assets/Models/troll.obj"));

		//Definimos canal de textura activo
		glActiveTexture(GL_TEXTURE0);

		//Generar textura
		GLuint textureID;
		glGenTextures(1, &textureID);

		//Vinculamos texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Configurar textura
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Cargar imagen a la textura
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureInfo);

		//Generar mipmap
		glGenerateMipmap(GL_TEXTURE_2D);

		//Liberar memoria de la imagen cargada
		stbi_image_free(textureInfo);
		
		//Generamos el game loop
		while (!glfwWindowShouldClose(GL_MANAGER.window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();
			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			camera.Inputs(GL_MANAGER.window); 
			camera.Update(); 

			troll.Awake();
			//Renderizo objeto 0
			models[0].Render();

			troll_2.Awake();
			models[0].Render();


			troll_3.Awake();
			models[0].Render();

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(GL_MANAGER.window);
		}

		//Desactivar y eliminar programa
		glUseProgram(0);
		PROGRAM_MANAGER.DeleteAllPrograms(); 

	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Finalizamos GLFW
	glfwTerminate();

}