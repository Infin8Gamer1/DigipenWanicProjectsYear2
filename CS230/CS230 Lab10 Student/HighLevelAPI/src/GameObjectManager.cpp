//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectManager.h"

// STD
#include <limits>

// Systems
#include <Graphics.h>	// GetWinMinX
#include "Space.h"		// GameObject->SetParent
#include "Event.h"

// Components
#include "Transform.h"	// IsOnScreen
#include "Collider.h"	// IsCollidingWith

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor
GameObjectManager::GameObjectManager(Space* space)
	: BetaObject("ObjectManager", space),
	fixedUpdateDt(1.0f / 60.0f), timeAccumulator(0.0f)
{
	// Reserve space for objects
	gameObjectActiveList.reserve(200);
	gameObjectArchetypes.reserve(10);
}

// Destructor
GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

// Update all objects in the active game objects list.
// (NOTE: After a game object has been updated, if it has been flagged as
//    destroyed, then it must be removed from the list and freed properly.
//    Additionally, the count of active objects must be reduced by 1.)
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManager::Update(float dt)
{
	Space* space = static_cast<Space*>(GetOwner());

	// Update objects if not paused
	if (space == nullptr || !space->IsPaused())
	{
		// Normal update for objects.
		VariableUpdate(dt);

		// Update physics/check for collisions.
		FixedUpdate(dt);

		//update events that are waiting to be broadcasted
		ProcessEvents(dt);
	}
	
	// Destroy objects marked for deletion.
	DestroyObjects();

	// Draw things!
	Draw();
}

// Shutdown the game object manager, destroying all active objects.
void GameObjectManager::Shutdown(void)
{
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); ++it)
	{
		delete (*it);
	}

	gameObjectActiveList.clear();
}

// Unload the game object manager, destroying all object archetypes.
void GameObjectManager::Unload(void)
{
	for (auto it = gameObjectArchetypes.begin(); it != gameObjectArchetypes.end(); ++it)
	{
		delete (*it);
	}

	gameObjectArchetypes.clear();
}

// Add a game object to the active game object list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddObject(GameObject& gameObject)
{
	// Okay to add one object
	gameObject.SetOwner(GetOwner());
	gameObject.Initialize();
	gameObjectActiveList.push_back(&gameObject);
}

// Add a game object to the game object archetype list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddArchetype(GameObject& gameObjectArchetype)
{
	// Okay to add one object
	gameObjectArchetypes.push_back(&gameObjectArchetype);
}

// Returns a pointer to the first active game object matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   If the named object is found,
//	   then return the pointer to the named game object,
//	   else return nullptr.
GameObject* GameObjectManager::GetObjectByName(const std::string& objectName) const
{
	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
	{
		if (objectName == (*it)->GetName())
			return *it;
	}

	return nullptr;
}

// Returns a pointer to the first game object archetype matching the specified name.
// Params:
//	 objectName = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return nullptr.
GameObject* GameObjectManager::GetArchetypeByName(const std::string& objectName) const
{
	for (auto it = gameObjectArchetypes.cbegin(); it != gameObjectArchetypes.cend(); ++it)
	{
		if (objectName == (*it)->GetName())
			return *it;
	}

	return nullptr;
}

// Returns the number of active objects with the given name.
// Params:
//   name = The name of the objects that should be counted.
unsigned GameObjectManager::GetObjectCount(const std::string& objectName) const
{
	unsigned count = 0;
	GameObject* current = nullptr;
	
	// Check for objects with specific name
	if (objectName != "")
	{
		for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
		{
			current = (*it);
			if (current->IsDestroyed() || current->GetName() != objectName)
				continue;

			++count;
		}
	}
	// If name is empty string, just return number of (not destroyed) objects
	else
	{
		for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
		{
			current = (*it);
			if (current->IsDestroyed())
				continue;

			++count;
		}
	}

	return count;
}

void GameObjectManager::DispatchEvent(Event * event)
{
	if (event->delay <= 0.0f)
	{
		if (event->receiver != GUID())
		{
			BetaObject *BObj = BetaObject::GetObjectByID(event->receiver);
			if (BObj != nullptr)
			{
				GameObject* obj = static_cast<GameObject*>(BObj);
				if (obj != nullptr)
				{
					obj->HandleEvent(*event);
				}
			}
		}
		else
		{
			for (size_t i = 0; i < gameObjectActiveList.size(); i++)
			{
				if (!gameObjectActiveList[i]->IsDestroyed())
				{
					gameObjectActiveList[i]->HandleEvent(*event);
				}
				
			}
		}

		delete event;
		event = nullptr;

	}
	else
	{
		events.push_back(event);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void GameObjectManager::ProcessEvents(float dt)
{
	for (std::vector<Event*>::iterator it = events.begin(); it != events.end();)
	{
		(*it)->delay -= dt;

		if ((*it)->delay <= 0.0f)
		{
			DispatchEvent((*it));

			it = events.erase(it);
		}
		else {
			it++;
		}
	}
}

// Update object logic using variable timestep.
void GameObjectManager::VariableUpdate(float dt)
{
	// Update active objects
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); ++it)
	{
		(*it)->Update(dt);
	}
}

// Update object physics using fixed timestep.
void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;

	while (timeAccumulator >= fixedUpdateDt)
	{
		// Update active objects (physics) with fixed dt
		for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); ++it)
		{
			(*it)->FixedUpdate(fixedUpdateDt);
		}

		// Check for collisions between pairs of objects
		CheckCollisions();

		// Decrease accumulator
		timeAccumulator -= fixedUpdateDt;
	}
}

// Destroy any objects marked for destruction.
void GameObjectManager::DestroyObjects()
{
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); )
	{
		// Remove destroyed objects
		if ((*it)->IsDestroyed())
		{
			delete (*it);
			it = gameObjectActiveList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

// Draw all game objects in the active game object list.
void GameObjectManager::Draw(void)
{
	for (auto it = gameObjectActiveList.begin(); it != gameObjectActiveList.end(); ++it)
	{
		// Draw object
		(*it)->Draw();
	}
}

// Check for collisions between each pair of objects
void GameObjectManager::CheckCollisions()
{
	for (auto i = gameObjectActiveList.begin(); i != gameObjectActiveList.end(); ++i)
	{
		GameObject* first = *i;

		// Skip inactive/destroyed
		if (first->IsDestroyed())
			continue;

		Collider* firstCollider = static_cast<Collider*>(first->GetComponent("Collider"));

		// Skip objects without colliders
		if (!firstCollider) 
			continue;

		for (auto j = i + 1; j != gameObjectActiveList.end(); ++j)
		{
			GameObject* second = *j;

			// Skip inactive/destroyed
			if (second->IsDestroyed())
				continue;

			Collider* secondCollider = static_cast<Collider*>(second->GetComponent("Collider"));

			// Skip objects without colliders
			if (!secondCollider) 
				continue;

			// Perform collision check and use callbacks if there is a collision
			firstCollider->CheckCollision(*secondCollider);
		}
	}
}
