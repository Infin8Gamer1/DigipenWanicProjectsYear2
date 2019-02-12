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
#include "MeshHelper.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Animation.h"
#include "Level1.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <gdiplus.h>
#include <Texture.h>
#include <Engine.h>
#include "Level3.h"
#include "Tilemap.h"
#include "MonkeyMovement.h"
#include <GameObjectFactory.h>
#include <ColliderTilemap.h>
#include <SpriteTilemap.h>
#include <ResourceManager.h>

Levels::Level2::Level2() : Level("Level2")
{
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::MonkeyMovement>();

	GameObject* Monkey = GameObjectFactory::GetInstance().CreateObject("Monkey");
	Monkey->GetComponent<Animation>()->Play(0, 8, 0.4f, false);
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
