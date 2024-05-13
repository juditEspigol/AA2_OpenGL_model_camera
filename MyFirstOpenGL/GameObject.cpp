#include "GameObject.h"

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color,
	Model _model, const char* _texture, GLuint _textureMode, int _textureIndex, GLuint _renderMode)
	: Object(_program, _position, _rotation, _scale), color(_color), model(_model), textureMode(_textureMode), textureIndex(_textureIndex), renderMode(_renderMode)
{
	hasTexture = true;
	textureInfo = stbi_load(_texture, &width, &height, &nrChannels, 0);
	InitTexture();
}

GameObject::GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color,
	Model _model, GLuint _renderMode)
	: Object(_program, _position, _rotation, _scale), color(_color), model(_model), renderMode(_renderMode) 
{
	hasTexture = false;
};

void GameObject::InitTexture()
{
	//Definimos canal de textura activo
	GLuint textureID;
	glActiveTexture(textureMode);

	//Generar textura
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
}

void GameObject::Update()
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(program);

	//Definir la matriz de traslacion, rotacion y escalado
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(rotation, rotation.x);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(rotation, rotation.y);
	rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(rotation, rotation.z);
	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(scale);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	if (hasTexture)
	{
		//Asignar valor variable de textura a usar.
		glUniform1i(glGetUniformLocation(program, "textureSampler"), textureIndex);
	}

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniform1i(glGetUniformLocation(program, "hasTexture"), hasTexture);

	// Pasar el color en que queremos pintar el game object
	glUniform4f(glGetUniformLocation(program, "ambientColor"), color[0], color[1], color[2], color[3]);
}

void GameObject::Render()
{
	//Vinculo su VAO para ser usado
	glBindVertexArray(model.GetVAO());

	// Dibujamos
	glDrawArrays(renderMode, 0, model.GetNumVertex());

	//Desvinculamos VAO
	glBindVertexArray(0);
}
