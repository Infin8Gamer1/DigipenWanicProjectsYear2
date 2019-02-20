//------------------------------------------------------------------------------
//
// File Name:	Level3.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Space.h"
#include "Level3.h"

//Other Levels
#include "Level1.h"
#include "Level2.h"

//Components
#include <Transform.h>
#include <Physics.h>
#include "ColorChange.h"
#include "ScreenWrap.h"

//Resources
#include "GameObject.h"

//Systems
#include <Input.h>
#include <GameObjectFactory.h>
#include <Graphics.h>
#include <ResourceManager.h>
#include <System.h>

Levels::Level3::Level3() : Level("Level3")
{
	circle2 = nullptr;
}

void Levels::Level3::Load()
{
	std::cout << "Level3::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::ColorChange>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::ScreenWrap>();
}

void Levels::Level3::Initialize()
{
	std::cout << "Level3::Initialize" << std::endl;

	GameObject* circle1 = GameObjectFactory::GetInstance().CreateObject("Circle");
	GetSpace()->GetObjectManager().AddObject(*circle1);

	circle2 = GameObjectFactory::GetInstance().CreateObject("Circle");
	//circle2->GetComponent<Physics>()->SetVelocity(Vector2D(400, 15));
	GetSpace()->GetObjectManager().AddObject(*circle2);

	GameObject* point = GameObjectFactory::GetInstance().CreateObject("Point");
	point->GetComponent<Physics>()->SetVelocity(Vector2D(0, -500));
	GetSpace()->GetObjectManager().AddObject(*point);

	GameObject* rectangle = GameObjectFactory::GetInstance().CreateObject("Rectangle");
	rectangle->GetComponent<Physics>()->SetVelocity(Vector2D(200, 200));
	GetSpace()->GetObjectManager().AddObject(*rectangle);

	GameObject* rectangle2 = GameObjectFactory::GetInstance().CreateObject("Rectangle");
	rectangle2->GetComponent<Physics>()->SetVelocity(Vector2D(-200, 400));
	GetSpace()->GetObjectManager().AddObject(*rectangle2);
}

void Levels::Level3::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	circle2->GetComponent<Transform>()->SetTranslation(Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition()));

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->SetLevel(new Levels::Level1());
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel(new Levels::Level2());
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Level3::Unload()
{
	std::cout << "Level3::Unload" << std::endl;

	ResourceManager::GetInstance().Shutdown();
}
