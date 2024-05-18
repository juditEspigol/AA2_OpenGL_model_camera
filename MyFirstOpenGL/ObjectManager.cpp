#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	delete camera; 

	for (GameObject* gObj : gameObjects)
		delete gObj;
}

void ObjectManager::CreateObjects()
{
	// 1. Set Camera
	camera = new Camera(glm::vec3(0.f, 0.25f, 1.2f));

	// 2. Set GaemObjects

	// TROLLS
	Model modelTroll = LoadOBJModel("Assets/Models/Troll.obj"); 
	Texture* textureTroll = new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0); 

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0], 
		Transform(glm::vec3(0.f, 0.25f, 1.1f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.15f)), 
		{ 0.5f, 1.f, 0.5f, 1.f },
		modelTroll, textureTroll, GL_TRIANGLES));
	
	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(-0.2f, 0.25f, 1.3f), glm::vec3(0.f, 80., 0.f), glm::vec3(0.1f)), 
		{ 1.f, 0.5f, 0.5f, 1.f }, 
		modelTroll, textureTroll, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.2f, 0.25f, 1.3f), glm::vec3(0.f, 280.f, 0.f), glm::vec3(0.1f)), 
		{ 0.5f, 0.5f, 1.f, 1.f }, 
		modelTroll, textureTroll, GL_TRIANGLES));

	// ROCKS
	Model modelRock = LoadOBJModel("Assets/Models/Rock.obj");
	Texture* textureRock = new Texture("Assets/Textures/Rock.png", GL_TEXTURE1, 1);

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.0f, 0.25f, 1.2f), glm::vec3(0.f, 0.f, 270.f), glm::vec3(0.05f)), 
		{ 0.9f, 0.9f, 0.9f, 1.f }, 
		modelRock, textureRock, GL_TRIANGLES));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.3f, 0.8f, 0.8f), glm::vec3(0.f, 0.f, 270.f), glm::vec3(0.15f)), 
		{ 0.3f, 0.3f, 0.3f, 1.f }, 
		modelRock, textureRock, GL_TRIANGLES));

	// CUBE
	Model modelPrimitive = LoadPrimitive({
		-0.2f, +0.2f, -0.2f, // 3
		+0.2f, +0.2f, -0.2f, // 2
		-0.2f, -0.2f, -0.2f, // 6
		+0.2f, -0.2f, -0.2f, // 7
		+0.2f, -0.2f, +0.2f, // 4
		+0.2f, +0.2f, -0.2f, // 2
		+0.2f, +0.2f, +0.2f, // 0
		-0.2f, +0.2f, -0.2f, // 3
		-0.2f, +0.2f, +0.2f, // 1
		-0.2f, -0.2f, -0.2f, // 6
		-0.2f, -0.2f, +0.2f, // 5
		+0.2f, -0.2f, +0.2f, // 4
		-0.2f, +0.2f, +0.2f, // 1
		+0.2f, +0.2f, +0.2f  // 0
		});

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[1],
		Transform (glm::vec3(0.0f, -0.16f, 1.25f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(2.f)), 
		{ 1.f, 0.8f, 0.4f, 1.f }, 
		modelPrimitive, nullptr, GL_TRIANGLE_STRIP));
}

void ObjectManager::Update(float _dt)
{
	camera->Update(_dt);
	camera->Inputs(GL_MANAGER.window);

	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
		gObj->Render();
	}

}
