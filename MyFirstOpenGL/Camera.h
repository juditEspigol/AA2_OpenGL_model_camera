#pragma once
#include "Object.h"

class Camera : public Object
{
public:

	glm::vec3 localVectorUp;

	float fov;
	float near;
	float far;

	Camera(GLuint _program, glm::vec3 _position, float _fov, float _near, float _far)
		: Object(_program, _position, glm::vec3(0.f), glm::vec3(1.0f)), fov(_fov), near(_near), far(_far),
		localVectorUp(glm::vec3(0.f, 1.f, 0.f)){ }; 

	void Update();

	void Inputs(GLFWwindow* _window);
};