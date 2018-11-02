//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"
#include "Level2.h"
#include <Engine.h>

Levels::Level2::Level2() : Level("Level2")
{
	lives = 2;
	maxHealth = 2;
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;
	currentHealth = maxHealth;
}

void Levels::Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//std::cout << "Level2::Update" << std::endl;
	currentHealth--;
	if (currentHealth == 0) {
		lives--;
		if (lives == 0) {
			Engine::GetInstance().Stop();
		} else {
			GetSpace()->RestartLevel();
		}
	}
}

void Levels::Level2::Shutdown()
{
	std::cout << "Level2::Shutdown" << std::endl;
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;
}
