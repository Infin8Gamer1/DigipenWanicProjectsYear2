//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

// BetaFramework Engine
#include <Engine.h>

// Engine modules
#include <Space.h>
#include <GameObjectFactory.h>

// Initial game state
#include "Level3.h"

// Custom components
#include "ColorChange.h"
#include "ScreenWrap.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Create a new space called "GameSpace"
	Space* space = new Space("GameSpace");

	// Set initial level to the second level.
	space->SetLevel<Levels::Level3>();

	// Add additional modules to engine
	Engine::GetInstance().AddModule(space);

	// Register custom components with object factory
	{
		using namespace Behaviors;
		GameObjectFactory::GetInstance().RegisterComponent<ColorChange>();
		GameObjectFactory::GetInstance().RegisterComponent<ScreenWrap>();
	}

	// Game engine goes!
	Engine::GetInstance().Start(1920, 1080);

	return 0;
}
