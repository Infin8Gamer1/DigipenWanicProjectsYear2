//------------------------------------------------------------------------------
//
// File Name:	Level3.cpp
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
#include "Level3.h"

// Systems
#include <Graphics.h>	// SetBackgroundColor
#include <Input.h>		// CheckTriggered
#include <Space.h>		// GetStateManager
#include <GameObjectFactory.h>

// Resources
#include "SpriteSource.h"	// SpriteSourceCreate
#include "Texture.h"		// CreateTextureFromFile
#include <MeshFactory.h>	// CreateMeshQuad
#include <Mesh.h>			// Mesh destructor

// Components
#include "Physics.h"
#include "Transform.h"

//------------------------------------------------------------------------------

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 1.
	Level3::Level3()
		: Level("Level3"), meshQuad(nullptr), textureCircle(nullptr),
		circleSpeed(2.0f), pointSpeed(1.0f)
	{
	}

	// Load the resources associated with the Level3 game state.
	void Level3::Load()
	{
		std::cout << "Level3: Load" << std::endl;

		// Create mesh
		meshQuad = MeshFactory::GetInstance().CreateQuadMesh();

		// Create a texture from Circle.png
		textureCircle = Texture::CreateTextureFromFile("Circle.png");
		spriteSourceCircle = new SpriteSource(textureCircle);
	}

	// Initialize the memory associated with the Level3 game state.
	void Level3::Initialize()
	{
		std::cout << "Level3: Initialize" << std::endl;

		// Create objects
		GameObject* circle = GameObjectFactory::GetInstance().CreateObject("Circle", meshQuad, spriteSourceCircle);
		GameObject* circle2 = GameObjectFactory::GetInstance().CreateObject("Circle", meshQuad, spriteSourceCircle);
		GameObject* point = GameObjectFactory::GetInstance().CreateObject("Point", meshQuad, spriteSourceCircle);
		GameObject* rectangle = GameObjectFactory::GetInstance().CreateObject("Rectangle", meshQuad);
		GameObject* rectangle2 = GameObjectFactory::GetInstance().CreateObject("Rectangle", meshQuad);

		// Set positions and velocities of objects
		Transform* transform = circle->GetComponent<Transform>();
		Physics* physics = circle->GetComponent<Physics>();
		transform->SetTranslation(Vector2D(-2, 2));
		physics->SetVelocity(Vector2D(1, -1) * circleSpeed);

		transform = circle2->GetComponent<Transform>();
		transform->SetTranslation(Vector2D(1.5, 2));

		transform = point->GetComponent<Transform>();
		physics = point->GetComponent<Physics>();
		transform->SetTranslation(Vector2D(0, 3));
		physics->SetVelocity(Vector2D(0, -1) * pointSpeed);

		transform = rectangle->GetComponent<Transform>();
		transform->SetTranslation(Vector2D());

		transform = rectangle2->GetComponent<Transform>();
		physics = rectangle2->GetComponent<Physics>();
		transform->SetTranslation(Vector2D(-1.5, -2));
		physics->SetVelocity(Vector2D(-1, 1) * pointSpeed);

		// Add objects to object manager
		GetSpace()->GetObjectManager().AddObject(*circle);
		GetSpace()->GetObjectManager().AddObject(*circle2);
		GetSpace()->GetObjectManager().AddObject(*point);
		GetSpace()->GetObjectManager().AddObject(*rectangle);
		GetSpace()->GetObjectManager().AddObject(*rectangle2);

		// Set Alpha Engine’s background color to black (0, 0, 0)
		Graphics::GetInstance().SetBackgroundColor(Colors::Black);
	}

	// Update the Level3 game state.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level3::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// If the user presses the 'R' key, restart the current level
		if (Input::GetInstance().CheckTriggered('R'))
			GetSpace()->RestartLevel();
	}

	// Unload the resources associated with the Level3 game state.
	void Level3::Unload()
	{
		// Free the mesh and texture.
		delete spriteSourceCircle;
		delete textureCircle;
		delete meshQuad;
	}
}
