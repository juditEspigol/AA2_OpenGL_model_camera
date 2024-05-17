#pragma once
#include "Object.h"

#include "Model.h"

class GameObject : public Object
{
private:

	GLuint program;

	Model model;
	glm::vec4 color; 

	bool hasTexture;
	GLuint textureMode, renderMode;
	
	int width, height, nrChannels;
	unsigned char* textureInfo;
	int textureIndex;

public:

	GameObject(GLuint _program, 
		Transform _transform, 
		glm::vec4 _color,
		Model _model, const char* _texture, GLuint _textureMode, int _textureIndex, GLuint _renderMode);

	GameObject(GLuint _program, 
		Transform _transform, 
		glm::vec4 _color,
		Model _model, GLuint _renderMode);

	void InitTexture();

	virtual void Update(float _dt) override; 
	virtual void Render();
};
