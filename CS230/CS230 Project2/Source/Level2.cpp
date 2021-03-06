//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
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

Levels::Level2::Level2() : Level("Level2")
{
	meshMonkey = nullptr;
	textureMonkey = nullptr;
	spriteSourceMonkey = nullptr;

	columns = 3;
	rows = 5;
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;

	Vector2D textureSize = Vector2D(1.0f / columns, 1.0f / rows);
	meshMonkey = CreateQuadMesh(textureSize, Vector2D(1, 1));

	textureMonkey = Texture::CreateTextureFromFile("Monkey.png");
	
	spriteSourceMonkey = new SpriteSource(columns, rows, textureMonkey);
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;

	GameObject* Monkey = Archetypes::CreateMonkey(meshMonkey, spriteSourceMonkey);
	static_cast<Animation*>(Monkey->GetComponent("Animation"))->Play(0, 8, 0.4f, false);
	GetSpace()->GetObjectManager().AddObject(*Monkey);
}

void Levels::Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->SetLevel(new Levels::Level1());
	} else if (Input::GetInstance().CheckReleased('2')) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;

	delete spriteSourceMonkey;
	spriteSourceMonkey = nullptr;
	delete meshMonkey;
	meshMonkey = nullptr;
	delete textureMonkey;
	textureMonkey = nullptr;
}
