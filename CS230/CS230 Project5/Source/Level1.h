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

#include <fmod.hpp>
#include "Vector2D.h"
#include <Level.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;
class SoundManager;

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
		
		// Update the Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Destroy objects associated with level 1.
		void Shutdown() override;

		// Unload the resources associated with Level 1.
		void Unload() override;

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Window Title
		const std::string WindowTitle = "Level 1";

		/*// Sound manager
		SoundManager* soundManager;
		FMOD::Channel* musicChannel;*/
	};
}

//----------------------------------------------------------------------------
