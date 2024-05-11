#pragma once
#include "GameObject.h"
#include "Camera.h"

#define GAMEOBJECT_MANAGER GameObjectManager::Instance()

class GameObjectManager
{
private:

	GameObjectManager() = default;

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

public:

	inline static GameObjectManager& Instance()
	{
		static GameObjectManager gameObjectManager;
		return gameObjectManager;
	}
	~GameObjectManager();

	std::vector<GameObject*> gameObjects;
	std::vector<Camera*> camera;

	void CreateFigures();

	void InitTexture();

	void Update();
};
