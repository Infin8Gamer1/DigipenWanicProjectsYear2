//------------------------------------------------------------------------------
//
// File Name:	Space.cpp
// Author(s):	Jeremy Kings
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"

#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
Space::Space(const std::string& name)
	: BetaObject(name), paused(false), currentLevel(nullptr), nextLevel(nullptr), objectManager(this)
{
}

// Destructor
Space::~Space()
{
	// Shutdown all systems
	Shutdown();
}

// Updates the state manager and object manager.
void Space::Update(float dt)
{
	// Initiate level change
	if (nextLevel != nullptr)
		ChangeLevel();

	// Update the current level
	if (currentLevel && !paused)
		currentLevel->Update(dt);

	// Update the object manager
	objectManager.Update(dt);
}

// Shuts down the object manager
void Space::Shutdown()
{
	// Shutdown current level
	if (currentLevel)
	{
		currentLevel->Shutdown();
		currentLevel->Unload();

		// Delete the current level
		delete currentLevel;
		currentLevel = nullptr;
	}

	// Shutdown and unload the object manager
	objectManager.Shutdown();
	objectManager.Unload();
}

// Accessors
bool Space::IsPaused() const
{
	return paused;
}

// Returns the name of the level currently running in this space.
const std::string & Space::GetLevelName() const
{
	return currentLevel->GetName();
}

// Pauses the space, preventing objects from being updated, but objects are still drawn.
void Space::SetPaused(bool value)
{
	paused = value;
}

void Space::SetLevel(Level* level)
{
	if (nextLevel != nullptr)
		return;

	nextLevel = level;
	nextLevel->SetOwner(this);
}

// Restarts the current level (next level = current)
void Space::RestartLevel()
{
	nextLevel = currentLevel;
}

// Returns the object manager, which you can use to retrieve and add objects.
GameObjectManager& Space::GetObjectManager()
{
	return objectManager;
}

// Game State Update
void Space::ChangeLevel()
{
	// Shutdown level
	if (currentLevel)
	{
		currentLevel->Shutdown();
		objectManager.Shutdown();
	}

	// If next level is not the same as current
	if (currentLevel != nextLevel)
	{
		// Unload level
		if (currentLevel)
		{
			currentLevel->Unload();
			objectManager.Unload();
		}

		// Delete current level
		delete currentLevel;
		// Set current level to next
		currentLevel = nextLevel;

		// Load level
		currentLevel->Load();
	}

	// Initialize level
	currentLevel->Initialize();

	// Reset next level pointer to null
	nextLevel = nullptr;
}
