#pragma once
#include "Object.h"

class Camera : public Object
{
private:

	int typeOfView = 0; 

	float fov;
	float near;
	float far;

	glm::vec3 centerOfView; 
	float distanceToCenter; 
	glm::vec3 eyeOrientation; 
	glm::vec3 angleIncrease; 

public:

	Camera(glm::vec3 _centerOfView = glm::vec3(0.f));

	Camera(Transform _transform, float _fov, float _near, float _far,
		glm::vec3 _centerOfView, float _distanceToCenter, glm::vec3 _eyeOrientation, glm::vec3 _angleIncrease);

	virtual void Update(float _dt) override;

	void Inputs(GLFWwindow* _window);

	inline void RelocateCenterOfView(const glm::vec3 _centerOfView) { centerOfView = _centerOfView; }; 
};