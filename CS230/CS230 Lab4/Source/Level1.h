//------------------------------------------------------------------------------
//
// File Name:	Level1.h
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

#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class Texture Texture;
typedef class SpriteSource SpriteSource;
typedef class Mesh Mesh;
typedef class Sprite Sprite;
typedef class Animation Animation;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Level1 : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 1.
		Level1();

		// Load the resources associated with Level 1.
		void Load() override;

		// Initialize the memory associated with Level 1.
		void Initialize() override;

		// Update Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Shutdown any memory associated with Level 1.
		void Shutdown() override;

		// Unload the resources associated with Level 1.
		void Unload() override;

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Meshe and texture for sprite source
		Mesh* mesh;
		Texture* texture;

		// Sprite and animation variables
		Sprite* sprite;

		// Level data
		unsigned lives;
	};
}

//----------------------------------------------------------------------------
