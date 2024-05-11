#pragma once
#include "GameObject.h"

class Primitive : public GameObject
{
private:

public:

	Primitive(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

	virtual void Awake();

	virtual void Render();
};