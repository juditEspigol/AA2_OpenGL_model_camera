#pragma once
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

#include "GLManager.h"

#include "MatrixUtilities.h"
#include <stb_image.h>

class Object
{
public:
	GLuint program;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Object(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		:program(_program), position(_position), rotation(_rotation), scale(_scale) {};

	virtual void Update() = 0;
};

