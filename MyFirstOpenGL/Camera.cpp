#include "Camera.h"
#include "ProgramManager.h"

Camera::Camera(glm::vec3 _centerOfView)
	: Object(Transform(glm::vec3(0.f, 1.f, 5.f), glm::vec3(0.f))),
	fov(45.f), near(0.1f), far(10.f), distanceToCenter(1.5f), angleIncrease(glm::vec3(0.f, 1.f, 0.f)),
	eyeOrientation(glm::vec3(0.f, 0.777f, 1.4f)), centerOfView(_centerOfView)
{};

Camera::Camera(Transform _transform, float _fov, float _near, float _far,
	glm::vec3 _centerOfView, float _distanceToCenter, glm::vec3 _eyeOrientation, glm::vec3 _angleIncrease)
	: Object(_transform), fov(_fov), near(_near), far(_far),
	distanceToCenter(_distanceToCenter), angleIncrease(_angleIncrease),
	eyeOrientation(_eyeOrientation), centerOfView(_centerOfView) 
{};


void Camera::Update(float _dt)
{
	if (typeOfView == 0)
	{
		// Convert the spherical coordinates to cartesian coordinates using the standard formula
		transform.position =
		{
			eyeOrientation.x + distanceToCenter * sin(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180)),
			eyeOrientation.y + distanceToCenter * sin(transform.rotation.z * (M_PI / 180)),
			eyeOrientation.z + distanceToCenter * cos(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180))
		};

		transform.rotation += angleIncrease * scaleTime;
	}
	else if (typeOfView == 1)
	{
		transform.position =
		{
			eyeOrientation.x + distanceToCenter * sin(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180)),
			eyeOrientation.y + distanceToCenter * sin(transform.rotation.z * (M_PI / 180)),
			eyeOrientation.z + distanceToCenter * cos(transform.rotation.y * (M_PI / 180)) * cos(transform.rotation.z * (M_PI / 180))
		};
	}

	// Matrix generation
	glm::mat4 view = glm::lookAt(transform.position, centerOfView, transform.up);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near, far);

	//Indicar a la tarjeta GPU que programa debe usar
	for (GLuint program : PROGRAM_MANAGER.compiledPrograms)
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}
}

void Camera::Inputs(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		transform.position.y += 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		transform.position.y -= 0.01f;
	}

	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		transform.position.x += 0.01f;
		transform.rotation.y += 1.0f;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		transform.position.x -= 0.01f;
		transform.rotation.y -= 1.f;
	}

	if (glfwGetKey(_window, GLFW_KEY_P) == GLFW_PRESS) {
		transform.position.z += 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_O) == GLFW_PRESS) {
		transform.position.z -= 0.01f;
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

	if (glfwGetKey(_window, GLFW_KEY_0) == GLFW_PRESS) {
		typeOfView = 0;

		// RESET TRANSFORM
		transform.position = glm::vec3(0.f, 1.f, 5.f); 
		transform.rotation = glm::vec3(0.f); 
		centerOfView = glm::vec3(0.f, 0.25f, 1.2f);
		eyeOrientation = glm::vec3(0.f, 0.777f, 1.4f); 
		distanceToCenter = 1.5f;
		scaleTime = 1.f; 
	}
	if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS) {
		typeOfView = 1;

		// RESET TRANSFORM
		transform.position = glm::vec3(0.f, 0.5f, 2.f);
		transform.rotation = glm::vec3(0.f, 120.f, 0.f);
		eyeOrientation = transform.position; 
		distanceToCenter = 0.25f;
		centerOfView = glm::vec3(-0.2f, 0.25f, 1.3f);
	}
	if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS) {
		typeOfView = 2;

		// RESET TRANSFORM
		transform.position = glm::vec3(0.f, 0.5f, 2.f);
		transform.rotation = glm::vec3(0.f);
		centerOfView = glm::vec3(0.2f, 0.25f, 1.3f) + glm::vec3(0.f, 0.f, -1.f);
	}
	if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS) {
		scaleTime = 0.f; 
	}
	if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS) {
		scaleTime = 1.f;
	}
}
