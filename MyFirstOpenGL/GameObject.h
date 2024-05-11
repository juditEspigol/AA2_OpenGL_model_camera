#pragma once
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

#include "GLManager.h"
#include "ModelManager.h"

#include "MatrixUtilities.h"
#include "Model.h"
#include <stb_image.h>

class GameObject
{
public:

	GLuint program; 

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::vector<float> color; 

	Model model;

	int width, height, nrChannels;
	unsigned char* textureInfo;
	int textureIndex;

	GLuint textureMode;

	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color = { 1.f, 1.f, 1.f, 1.f, },
		Model _model = MODEL_MANAGER.models[0], const char* _texture = "Assets/Textures/Troll.png", GLuint _textureMode = GL_TEXTURE0, int _textureIndex = 0)
		: program(_program), position(_position), rotation(_rotation), scale(_scale), color(_color), model(_model), textureMode(_textureMode), 
		textureIndex(_textureIndex)
	{
		textureInfo = stbi_load(_texture, &width, &height, &nrChannels, 0);
		InitTexture();
	}; 

	void InitTexture();

	void Awake();

	void Render();
};