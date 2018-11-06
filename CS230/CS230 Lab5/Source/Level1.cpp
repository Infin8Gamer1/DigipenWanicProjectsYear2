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
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Engine.h>

Levels::Level1::Level1() : Level("Level1")
{
	sprite = nullptr;
	mesh = nullptr;
	texture = nullptr;
	transform = nullptr;
}

void Levels::Level1::Load()
{
	std::cout << "Level1::Load" << std::endl;
	mesh = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	//mesh = CreateQuadMesh(Vector2D(0, 0), Vector2D(0, 0));
}

void Levels::Level1::Initialize()
{
	std::cout << "Level1::Initialize" << std::endl;

	transform = new Transform(Vector2D(100,-100), Vector2D(300,150), 40.0f);

	sprite = new Sprite(transform);
	sprite->SetMesh(mesh);
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//std::cout << "Level1::Update" << std::endl;
	sprite->Draw();

	if (Input::GetInstance().CheckTriggered('2')) {
		GetSpace()->SetLevel(new Levels::Level2());
	} else if (Input::GetInstance().CheckTriggered('1')) {
		GetSpace()->RestartLevel();
	} else if (Input::GetInstance().CheckTriggered(' ')) {
		Engine::GetInstance().Stop();
	}
}

void Levels::Level1::Shutdown()
{
	std::cout << "Level1::Shutdown" << std::endl;
	delete sprite;
	sprite = nullptr;
	delete transform;
	transform = nullptr;
}

void Levels::Level1::Unload()
{
	std::cout << "Level1::Unload" << std::endl;
	delete mesh;
	mesh = nullptr;
}
