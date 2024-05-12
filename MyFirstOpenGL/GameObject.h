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
		Model _model, const char* _texture, GLuint _textureMode, int _textureIndex, bool _hasTexture, GLuint _renderMode)
		: Object(_program, _position, _rotation, _scale), color(_color), model(_model), textureMode(_textureMode),
		textureIndex(_textureIndex), hasTexture(_hasTexture), renderMode(_renderMode)
	{
		if (hasTexture)
		{
			textureInfo = stbi_load(_texture, &width, &height, &nrChannels, 0);
			InitTexture();		
		}

	}; 

	void InitTexture();

	virtual void Update();

	virtual void Render();
};