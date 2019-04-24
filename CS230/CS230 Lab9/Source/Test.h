//------------------------------------------------------------------------------
//
// File Name:	Test.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Project7
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

class PostEffect;
class Graphics;
class Input;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Test : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Create an instance of the Test level.
		Test();

		// Load the resources associated with the Test level.
		void Load() override;

		// Initialize the memory associated with the Test level.
		void Initialize() override;

		// Update the Test level.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with the Test level.
		void Unload() override;

	private:
		//------------------------------------------------------------------------------
		// Private Function Declarations:
		//------------------------------------------------------------------------------

		void MoveCamera(float dt);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// HUD Space
		Space* hudSpace;

		// Effects
		PostEffect* fadeToBlack;
		PostEffect* invertColors;
		PostEffect* vignette;
		PostEffect* noise;
		PostEffect* scanline;

		// Systems
		Graphics* graphics;
		Input* input;
	};
}

//------------------------------------------------------------------------------
