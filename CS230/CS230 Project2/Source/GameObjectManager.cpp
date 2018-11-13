#include "stdafx.h"
#include "GameObjectManager.h"
#include "Space.h"
#include "GameObject.h"

GameObjectManager::GameObjectManager(Space * space) : BetaObject("ObjectManager", space)
{
	timeAccumulator = 0.0f;
	numArchetypes = 0;
	numObjects = 0;
}

GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

void GameObjectManager::Update(float dt)
{
	if (!static_cast<Space*>(GetParent())->IsPaused()) {
		VariableUpdate(dt);
		FixedUpdate(dt);
	}
	DestroyObjects();
	Draw();
}

void GameObjectManager::Shutdown(void)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		delete gameObjectActiveList[i];
		gameObjectActiveList[i] = nullptr;
	}

	numObjects = 0;
}

void GameObjectManager::Unload(void)
{
	for (size_t i = 0; i < numArchetypes; i++)
	{
		delete gameObjectArchetypes[i];
		gameObjectArchetypes[i] = nullptr;
	}

	numArchetypes = 0;
}

void GameObjectManager::AddObject(GameObject & _gameObject)
{
	//_gameObject.SetParent(GetParent());
	//_gameObject.Initialize();
	if (numObjects + 1 < maxObjects) {
		gameObjectActiveList[numObjects] = &_gameObject;
		gameObjectActiveList[numObjects]->SetParent(GetParent());
		gameObjectActiveList[numObjects]->Initialize();

		numObjects++;
	}
	else {
		std::cout << "added too many objects!" << std::endl;
		//_gameObject.~GameObject();
	}
}

void GameObjectManager::AddArchetype(GameObject & _gameObject)
{
	if (numArchetypes + 1 < maxArchetypes) {
		gameObjectArchetypes[numArchetypes + 1]->operator=(_gameObject);
		numArchetypes++;
	}
	else {
		std::cout << "added too many Archetypes!" << std::endl;
		//_gameObject.~GameObject();
	}
}

GameObject * GameObjectManager::GetObjectByName(const std::string & objectName) const
{
	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName) {
			return gameObjectActiveList[i];
		}
	}
	std::cout << "Couldn't find object with name of " << objectName << "." << std::endl;
	return nullptr;
}

GameObject * GameObjectManager::GetArchetypeByName(const std::string & objectName) const
{
	for (size_t i = 0; i < numArchetypes; i++)
	{
		if (gameObjectArchetypes[i]->GetName() == objectName) {
			return gameObjectArchetypes[i];
		}
	}
	std::cout << "Couldn't find archetype with name of " << objectName << "." << std::endl;
	return nullptr;
}

unsigned GameObjectManager::GetObjectCount(const std::string & objectName) const
{
	int output = 0;

	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->GetName() == objectName && !gameObjectActiveList[i]->IsDestroyed()) {
			output++;
		}
	}

	return output;
}

void GameObjectManager::VariableUpdate(float dt)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Update(dt);
		//gameObjectActiveList[i]->FixedUpdate(dt);
	}
}

void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;

	if (timeAccumulator >= fixedUpdateDt)
	{
		for (size_t i = 0; i < numObjects; i++)
		{
			gameObjectActiveList[i]->FixedUpdate(fixedUpdateDt);
		}

		timeAccumulator -= fixedUpdateDt;
	}
}

void GameObjectManager::DestroyObjects()
{
	for (size_t i = 0; i < numObjects; i++)
	{
		if (gameObjectActiveList[i]->IsDestroyed()) {
			//destroy components on gameobject
			gameObjectActiveList[i]->~GameObject();
			//delete the memory assosiated with it
			delete gameObjectActiveList[i];
			gameObjectActiveList[i] = nullptr;
			//shift the array so that there isn't a gap
			for (size_t z = i; z < numObjects; z++)
			{
				gameObjectActiveList[z] = gameObjectActiveList[z + 1];
			}
			//delete the memory assosiated with the final object
			delete gameObjectActiveList[numObjects];
			gameObjectActiveList[numObjects] = nullptr;
			//decrease the number of objects
			numObjects--;
		}
	}
}

void GameObjectManager::Draw(void)
{
	for (size_t i = 0; i < numObjects; i++)
	{
		gameObjectActiveList[i]->Draw();
	}
}
