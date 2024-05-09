#pragma once
#include <glm.hpp>
#include <vector>

class GameObject
{
public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::vector<float> color; 

	GameObject(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::vector<float> _color = {0.f, 0.f, 0.f, 0.f,})
		: position(_position), rotation(_rotation), scale(_scale), color(_color)
	{}; 
};