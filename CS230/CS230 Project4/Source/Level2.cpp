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

//Other Levels
#include "Level1.h"
#include "Level3.h"

//Components
#include <Animation.h>
#include "MonkeyMovement.h"
#include <GameObject.h>

//Systems
#include <Input.h>
#include <GameObjectFactory.h>
#include <ResourceManager.h>
#include <System.h>

Levels::Level2::Level2() : Level("Level2")
{
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::MonkeyMovement>();
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	GameObject* Monkey = GameObjectFactory::GetInstance().CreateObject("Monkey");
	//Monkey->GetComponent<Animation>()->Play(0.4f, false);
	GetSpace()->GetObjectManager().AddObject(*Monkey);

	GameObject* Map = GameObjectFactory::GetInstance().CreateObject("tileMap");
	GetSpace()->GetObjectManager().AddObject(*Map);
}

void Levels::Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->SetLevel(new Levels::Level1());
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel(new Levels::Level3());
	}
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;

	ResourceManager::GetInstance().Shutdown();
}
