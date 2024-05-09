#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:

	glm::vec3 localVectorUp;

	float fov;
	float near;
	float far;

	Camera(glm::vec3 _position, float _fov, float _near, float _far)
		: GameObject(_position, glm::vec3(0.f), glm::vec3(1.0f)), fov(_fov), near(_near), far(_far),
		localVectorUp(glm::vec3(0.f, 1.f, 0.f))
	{ }; 

	void Inputs(GLFWwindow* _window)
	{
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
			position.y += 0.01f;
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
			position.y -= 0.01f;
		}

		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
			position.x += 0.01f;
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
			position.x -= 0.01f;
		}

		if (glfwGetKey(_window, GLFW_KEY_P) == GLFW_PRESS) {
			position.z += 0.01f;
		}
		if (glfwGetKey(_window, GLFW_KEY_O) == GLFW_PRESS) {
			position.z -= 0.01f;
		}

		if (glfwGetKey(_window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
			fov += 1.f;
			if (fov >= 179)
				fov = 179;
		}
		if (glfwGetKey(_window, GLFW_KEY_COMMA) == GLFW_PRESS) {
			fov -= 1.f;
			if (fov < 1.f)
				fov = 1.f;
		}
	}; 
};