//------------------------------------------------------------------------------
//
// File Name:	Level2.h
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
	class Level2 : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 2.
		Level2();

		// Load the resources associated with Level 2.
		void Load();

		// Initialize the memory associated with Level 2.
		void Initialize();

		// Update Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt);

		// Shutdown any memory associated with Level 2.
		void Shutdown();

		// Unload the resources associated with Level 2.
		void Unload();

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Meshe and texture for sprite source
		Mesh* mesh;
		Texture* texture;

		// Sprite source variables
		SpriteSource* spriteSource;
		unsigned columns;
		unsigned rows;

		// Sprite and animation variables
		Sprite* sprite;
		Animation* animation;

		// Level data
		unsigned lives;
		unsigned maxHealth;
		unsigned currentHealth;
	};
}

//----------------------------------------------------------------------------
