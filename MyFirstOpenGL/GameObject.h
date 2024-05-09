#pragma once
#include <glm.hpp>

class GameObject
{
public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	GameObject(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: position(_position), rotation(_rotation), scale(_scale) 
	{}; 

	void ChangeColor(glm::vec4 _ambientColor = glm::vec4(0.f, 0.f, 0.f, 1.f))
	{

	}
};