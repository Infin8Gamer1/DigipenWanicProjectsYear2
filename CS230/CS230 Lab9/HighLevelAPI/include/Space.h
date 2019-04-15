//------------------------------------------------------------------------------
//
// File Name:	Space.h
// Author(s):	Jeremy Kings
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <GameObjectManager.h>	// composition
#include <ResourceManager.h>	// composition
#include <BetaObject.h> // inheritance
#include <Camera.h>		// Reset

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Level;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Space : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor(s)
	Space(const std::string& name, bool customCamera = false);

	// Destructor
	~Space();

	// Updates the state manager and object manager.
	void Update(float dt);

	// Shuts down the object manager
	void Shutdown();

	// Returns a boolean indicating whether objects in this space are paused.
	bool IsPaused() const;

	// Returns the name of the level currently running in this space.
	std::string GetLevelName() const;

	// Returns the object manager, which you can use to retrieve and add objects.
	GameObjectManager& GetObjectManager();

	// Returns the resource manager, which handles sprite sources, meshes and sounds.
	ResourceManager& GetResourceManager();

	// Pauses the space, preventing objects from being updated, but objects are still drawn.
	void SetPaused(bool value);

	// Sets the level that the space is using after unloading the current level.
	template <class LevelType>
	void SetLevel()
	{
		if (currentLevel != nullptr && typeid(LevelType) == typeid(*currentLevel))
		{
			RestartLevel();
		}
		else
		{
			nextLevel = new LevelType();
			nextLevel->SetOwner(this);
		}

		// Reset camera
		GetCamera().Reset();
	}

	// Restarts the current level (next level = current)
	void RestartLevel();

	// Checks whether space should be destroyed
	bool IsDestroyed() const;

	// Marks the space for destruction
	void Destroy();

	// Get the camera used by this space.
	Camera& GetCamera() const;

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Updates current/next level pointers and calls shutdown/unload/load/init
	void ChangeLevel();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	bool paused;
	BetaObject* currentLevel;
	BetaObject* nextLevel;
	GameObjectManager objectManager;
	ResourceManager resourceManager;
	bool isDestroyed;
	Camera* camera;
	bool customCamera;
};

//------------------------------------------------------------------------------
