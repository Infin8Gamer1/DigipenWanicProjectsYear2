//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "GameObject.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Quadtree;
class Space;
class Vector2D;
struct CastResult;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public functions declared in the header.
class GameObjectManager : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor(s)
	GameObjectManager(Space* space);

	// Destructor
	~GameObjectManager();

	// Update all objects in the active game objects list.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Shutdown the game object manager, destroying all active objects.
	void Shutdown(void) override;

	// Unload the game object manager, destroying all object archetypes.
	void Unload(void) override;

	// Add a game object to the active game object list.
	// Params:
	//	 gameObject = Reference to the game object to be added to the list.
	void AddObject(GameObject& gameObject);

	// Add a game object to the game object archetype list.
	// Params:
	//	 gameObject = Reference to the game object to be added to the list.
	void AddArchetype(GameObject& gameObject);

	// Returns a pointer to the first active game object matching the specified name.
	// Params:
	//	 name = The name of the object to be returned, if found.
	// Returns:
	//   If the named object is found,
	//	   then return the pointer to the named game object,
	//	   else return nullptr.
	GameObject* GetObjectByName(const std::string& name) const;

	// Returns a pointer to the first game object archetype matching the specified name.
	// Params:
	//	 name = The name of the archetype to be returned, if found.
	//   createIfNotFound = Whether to create the archetype using the 
	//		factory if it isn't in the archetype list.
	// Returns:
	//   If the named archetype is found,
	//	   then return the pointer to the named game object archetype,
	//	   else return nullptr.
	GameObject* GetArchetypeByName(const std::string& name, bool createIfNotFound = false);

	// Returns the number of active objects with the given name.
	// Params:
	//   objectName = The name of the objects that should be counted.
	unsigned GetObjectCount(const std::string& objectName) const;

	// Retrieves all objects that contain the given component.
	template<typename ComponentType>
	void GetAllObjectsWithComponent(std::vector<GameObject*>& results)
	{
		for (unsigned i = 0; i < objects.size(); ++i)
		{
			if (objects[i]->GetComponent<ComponentType>() != nullptr)
				results.push_back(objects[i]);
		}
	}

	// Test whether the quadtree is currently enabled for this object manager.
	bool IsQuadtreeEnabled() const;

	// Enable or disable use of the quadtree data structure for collision detection.
	void SetQuadtreeEnabled(bool enabled);

	// Perform a raycast and return all objects that intersect with the ray.
	// Params:
	//   start     = The starting point of the ray in world coordinates.
	//   direction = The direction of the ray.
	//   distance  = How far to check in the given direction.
	//   results   = The vector in which the results will be stored.
	//   filter    = Objects with this name are excluded.
	void CastRay(const Vector2D& start, const Vector2D& direction, float distance, 
		std::vector<CastResult>& results, const std::string& filter = "");

	// Perform a raycast and return the first object hit.
	// Params:
	//   start     = The starting point of the ray in world coordinates.
	//   direction = The direction of the ray.
	//   distance  = How far to check in the given direction.
	//   filter    = Objects with this name are excluded.
	// Returns:
	//   A pointer to the first object hit by the ray.
	GameObject* CastRayClosest(const Vector2D& start, const Vector2D& direction, 
		float distance, const std::string& filter = "");

private:
	// Disable copy constructor and assignment operator
	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;

	// Update object logic using variable timestep.
	void VariableUpdate(float dt);

	// Update object physics using fixed timestep.
	void FixedUpdate(float dt);

	// Check collisions between pairs of objects.
	void CheckCollisions();

	// Check collisions using the quadtree.
	void CheckCollisionsQuadtree();

	// Destroy any objects marked for destruction.
	void DestroyObjects();

	// Draw all game objects in the active game object list.
	void Draw(void) override;

	// Instantiate the quadtree using the current world size.
	void RemakeQuadtree();

	// Inserts objects into the quadtree
	void PopulateQuadtree();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	std::vector<GameObject*> objects;
	std::vector<GameObject*> archetypes;
	float timeAccumulator;
	const float fixedUpdateDt;

	Quadtree* quadtree;
	bool quadtreeEnabled;
	std::vector<GameObject*> collidableObjects;
};

//------------------------------------------------------------------------------
