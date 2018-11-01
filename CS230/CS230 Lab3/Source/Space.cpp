//------------------------------------------------------------------------------
//
// File Name:	Space.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"
#include "Level.h"

Space::Space(const std::string & name) : BetaObject(name)
{
	paused = false;
	currentLevel = nullptr;
	nextLevel = nullptr;
}

Space::~Space()
{
	Shutdown();
}

void Space::Update(float dt)
{
	std::cout << "Space::Update";

	if (nextLevel != nullptr) {
		ChangeLevel();
	}
	if (currentLevel != nullptr && !paused) {
		currentLevel->Update(dt);
	}
}

void Space::Shutdown()
{
	if (currentLevel != nullptr) {
		currentLevel->Shutdown();
		currentLevel->Unload();
		currentLevel = nullptr;
	}
}

bool Space::IsPaused() const
{
	return paused;
}

const std::string & Space::GetLevelName() const
{
	return GetName();
}

void Space::SetPaused(bool value)
{
	paused = value;
}

void Space::SetLevel(Level * level)
{
	nextLevel = level;
	nextLevel->SetParent(this);
}

void Space::RestartLevel()
{
	SetLevel(currentLevel);
}

void Space::ChangeLevel()
{
	if (currentLevel == nextLevel) {
		//Restarting Level
		currentLevel->Shutdown();
		currentLevel->Initialize();
	} else {
		//switching levels
		if (currentLevel != nullptr) {
			currentLevel->Shutdown();
			currentLevel->Unload();
		}
		nextLevel->Load();
		nextLevel->Initialize();
	}

	currentLevel = nextLevel;
	nextLevel = nullptr;
}
