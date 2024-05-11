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
		glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.5f), { 0.5f, 1.f, 0.5f, 1.f }, MODEL_MANAGER.models[0], 
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0));
	
	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(-0.5f, 0.f, 0.5f), glm::vec3(0.f, 45.f, 0.f), glm::vec3(0.25f), { 1.f, 0.5f, 0.5f, 1.f }, MODEL_MANAGER.models[0],
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.f, 300.f, 0.f), glm::vec3(0.25f), { 0.5f, 0.5f, 1.f, 1.f }, MODEL_MANAGER.models[0],
		"Assets/Textures/Troll.png", GL_TEXTURE0, 0));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.25f), { 1.f, 1.f, 1.f, 1.f }, MODEL_MANAGER.models[1],
		"Assets/Textures/Rock.png", GL_TEXTURE1, 1));

}

void GameObjectManager::InitTexture()
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->InitTexture();
	}
}

void GameObjectManager::Update()
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->Awake();
		gObj->Render();
	}

	for (Camera* cam : camera)
	{
		cam->Inputs(GL_MANAGER.window);
		cam->Update();
	}

}
