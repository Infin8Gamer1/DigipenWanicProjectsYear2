//------------------------------------------------------------------------------
//
// File Name:	Omega.h
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

#include <Level.h>
#include <fmod.hpp>
#include "PlayerShip.h"
#include <SpriteText.h>
#include <iostream>
#include <vector>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Mesh;
class SpriteSource;
class Texture;
class SoundManager;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Omega : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Create an instance of the Omega game state.
		Omega();

		// Load archetypes, meshes
		void Load();

		// Initialize the memory associated with the Omega game state.
		void Initialize();

		// Update the Omega game state.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt);

		// Set high score
		void Shutdown();

		// Unload textures, sprite sources, meshes
		void Unload();

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------
	
		// Create a single asteroid object from the archetype
		void SpawnAsteroid(void);

		// Create a group of asteroids
		void SpawnAsteroidWave(void);

		// Update the score string
		void UpdateScore();

		// Switch levels when keys are pressed
		void SwitchLevels();

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Spawning
		const unsigned asteroidSpawnInitial = 8;
		const unsigned asteroidSpawnMaximum = 20;
		unsigned asteroidSpawnCount;
		unsigned asteroidWaveCount;

		// Player
		Behaviors::PlayerShip* playerShip;
		unsigned asteroidHighScore;

		//scoreTracker
		SpriteText* scoreText;
		
		// Window Title
		const std::string WindowTitle = "Omega";

		// Sound manager
		SoundManager* soundManager;
		FMOD::Channel* musicChannel;

		GameObject* Line;

		//// Resources
		//Mesh* mesh;
		//Texture* textureShip;
		//Texture* textureBullet;
		//Texture* textureAsteroid;
		//SpriteSource* spriteShip;
		//SpriteSource* spriteBullet;
		//SpriteSource* spriteAsteroid;
	};
}

//----------------------------------------------------------------------------
