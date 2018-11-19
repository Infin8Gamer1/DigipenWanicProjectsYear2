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
#include "MeshHelper.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Engine.h>
#include "Level3.h"

Levels::Level1::Level1() : Level("Level1")
{
	meshShip = nullptr;
	meshBullet = nullptr;
}

void Levels::Level1::Load()
{
	std::cout << "Level1::Load" << std::endl;
	meshShip = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	meshBullet = CreateTriangleMesh(Color(1, 0, 0), Color(1, 0, 0), Color(1, 0, 0));

	GameObject* Bullet = Archetypes::CreateBulletArchetype(meshBullet);
	GetSpace()->GetObjectManager().AddArchetype(*Bullet);
}

void Levels::Level1::Initialize()
{
	std::cout << "Level1::Initialize" << std::endl;

	GameObject* Ship = Archetypes::CreateShip(meshShip);
	GetSpace()->GetObjectManager().AddObject(*Ship);
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//std::cout << "Level1::Update" << std::endl;

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel(new Levels::Level2());
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel(new Levels::Level3());
	}
}

void Levels::Level1::Unload()
{
	std::cout << "Level1::Unload" << std::endl;

	delete meshShip;
	meshShip = nullptr;
	delete meshBullet;
	meshBullet = nullptr;
}
