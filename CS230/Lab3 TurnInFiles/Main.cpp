//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
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
#include "Space.h"
#include "Level1.h"

// BetaFramework Engine
#include <Engine.h>

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

	// TO-DO: Redirect std::cout to trace.txt
	std::ofstream fileOutput("trace.txt");
	std::cout.rdbuf(fileOutput.rdbuf());

	// TO-DO: Create a space
	Space* GameSpace = new Space("GameSpace");
	// TO-DO: Set initial level to the first level
	GameSpace->SetLevel(new Levels::Level1());
	// TO-DO: Add additional modules to engine
	Engine::GetInstance().AddModule(GameSpace);
	// TO-DO: Print Engine::Start using cout
	std::cout << "Engine::Start" << std::endl;
	// Game engine goes!
	Engine::GetInstance().Start(instance, 800, 600);

	// TO-DO: Print Engine::Stop using cout
	std::cout << "Engine::Stop" << std::endl;
	return 0;
}
