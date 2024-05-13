#include "GameObjectManager.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject* gObj : gameObjects)
	{
		delete gObj;
	}
}

void GameObjectManager::CreateFigures()
{
	camera.push_back(new Camera(PROGRAM_MANAGER.compiledPrograms[0], glm::vec3(0.f, 0.5f, 2.f), 45.0f, 0.1f, 10.f));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.f, 0.25f, 1.1f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.15f), { 0.5f, 1.f, 0.5f, 1.f }, MODEL_MANAGER.models[0], 
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0, GL_TRIANGLES));
	
	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(-0.2f, 0.25f, 1.3f), glm::vec3(0.f, 80., 0.f), glm::vec3(0.1f), { 1.f, 0.5f, 0.5f, 1.f }, MODEL_MANAGER.models[0],
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.2f, 0.25f, 1.3f), glm::vec3(0.f, 280.f, 0.f), glm::vec3(0.1f), { 0.5f, 0.5f, 1.f, 1.f }, MODEL_MANAGER.models[0],
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.0f, 0.25f, 1.2f), glm::vec3(0.f, 0.f, 270.f), glm::vec3(0.05f), { 0.9f, 0.9f, 0.9f, 1.f }, MODEL_MANAGER.models[1],
		"Assets/Textures/Rock.png", GL_TEXTURE1, 1, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.3f, 0.8f, 0.8f), glm::vec3(0.f, 0.f, 270.f), glm::vec3(0.15f), { 0.3f, 0.3f, 0.3f, 1.f }, MODEL_MANAGER.models[1],
		"Assets/Textures/Rock.png", GL_TEXTURE1, 1, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.0f, -0.16f, 1.1f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(2.f), { 1.f, 0.8f, 0.4f, 1.f }, MODEL_MANAGER.models[2], GL_TRIANGLE_STRIP));
}

void GameObjectManager::Update()
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->Update();
		gObj->Render();
	}

	for (Camera* cam : camera)
	{
		cam->Update();
		cam->Inputs(GL_MANAGER.window);
	}

}
