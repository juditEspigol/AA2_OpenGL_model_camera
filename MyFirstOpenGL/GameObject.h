#pragma once
#include <glm.hpp>
#include <vector>

class GameObject
{
public:

	GLuint program; 

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::vector<float> color; 

	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color = {1.f, 1.f, 1.f, 1.f,})
		: program(_program), position(_position), rotation(_rotation), scale(_scale), color(_color)
	{}; 

	void Awake()
	{
		//Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(program);

		//Definir la matriz de traslacion, rotacion y escalado
		glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(position);
		glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(rotation, rotation.y);
		glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(scale);

		//Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

		//Asignar valor variable de textura a usar.
		glUniform1i(glGetUniformLocation(program, "textureSampler"), 0);

		// Pasar las matrices
		glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

		// Pasar el color en que queremos pintar el game object
		glUniform4f(glGetUniformLocation(program, "ambientColor"), color[0], color[1], color[2], color[3]);
	}
};