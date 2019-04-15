//------------------------------------------------------------------------------
//
// File Name:	SpaceManager.h
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

#include "BetaObject.h"
#include "Space.h"

#include <vector>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class SpaceManager : public BetaObject
{
public:
	// Constructor - creates the default game space.
	SpaceManager();

	// Destructor - deletes all spaces.
	~SpaceManager();

	// Initialize the space manager.
	void Initialize() override;

	// Updates all spaces and destroys those that are ready for destruction.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Shuts down the space manager, destroying all spaces.
	void Shutdown() override;

	// Creates a new space with the given name
	// Params:
	//   name = The name of the newly created space.
	//   useCustomCamera = Whether this space should have its own camera.
	Space* AddSpace(const std::string& name, bool useCustomCamera);

	// Returns a pointer to the space with the given name.
	// Returns nullptr if no such space exists.
	Space* GetSpaceByName(const std::string& name) const;

	// Returns the default space for game objects
	Space& GetDefaultSpace();

private:
	// Pointers to all spaces
	std::vector<Space*> spaces;

	// Default space for game objects
	Space* gameSpace;
};
