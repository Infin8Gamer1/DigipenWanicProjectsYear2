//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Level1.h"
#include "Level2.h"
#include "Space.h"
#include <Engine.h>

Levels::Level1::Level1() : Level("Level1")
{
	lives = 3;
}

void Levels::Level1::Load()
{
	std::cout << "Level1::Load" << std::endl;
}

void Levels::Level1::Initialize()
{
	std::cout << "Level1::Initialize" << std::endl;
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//std::cout << "Level1::Update" << std::endl;
	lives -= 1;

	if (lives == 0) {
		GetSpace()->SetLevel(new Levels::Level2());
	}
}

void Levels::Level1::Shutdown()
{
	std::cout << "Level1::Shutdown" << std::endl;
}

void Levels::Level1::Unload()
{
	std::cout << "Level1::Unload" << std::endl;
}
