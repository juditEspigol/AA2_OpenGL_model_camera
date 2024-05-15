#include "Camera.h"

void Camera::Update()
{
	float camX =  1.5 * -sinf(rotation.x * (3.141516 / 180)) * cosf((rotation.y) * (3.141516 / 180));
	float camY =  1.5 * -sinf((rotation.y) * (3.141516 / 180));
	float camZ = -1.5 * cosf((rotation.x) * (3.141516 / 180)) * cosf((rotation.y) * (3.141516 / 180));

	//Genero la matriz vista
	glm::mat4 view = glm::lookAt(glm::vec3(0.f, 0.777f, 1.4f) + glm::vec3(camY, camX, camZ), glm::vec3(0.0f, 0.25f, 1.2f), localVectorUp);
	// Definir la matriz proyeccion
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near, far);

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::Inputs(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		position.y += 0.01f;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		position.y -= 0.01f;
	}

	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		position.x += 0.01f;
		rotation.y += 1.0f; 
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		position.x -= 0.01f;
		rotation.y -= 1.f; 
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
}
