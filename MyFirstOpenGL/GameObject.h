#pragma once
#include "Object.h"

#include "ModelManager.h"
#include "Model.h"

class GameObject : public Object
{
private:
	std::vector<float> color; 

	Model model;

	int width, height, nrChannels;
	unsigned char* textureInfo;
	int textureIndex;

	GLuint textureMode, renderMode;

	bool hasTexture;

public:
	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color,
		Model _model, const char* _texture, GLuint _textureMode, int _textureIndex, GLuint _renderMode);
	GameObject(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color,
		Model _model, GLuint _renderMode);

	void InitTexture();

	virtual void Update();

	virtual void Render();
};