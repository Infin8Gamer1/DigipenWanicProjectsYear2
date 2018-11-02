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
#include <gdiplus.h>
#include <Texture.h>
#include <Engine.h>

Levels::Level2::Level2() : Level("Level2")
{
	mesh = nullptr;
	texture = nullptr;

	spriteSource = nullptr;
	columns = 1;
	rows = 1;

	sprite = nullptr;
	animation = nullptr;
	
	lives = 2;
	maxHealth = 2;
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;
	mesh = CreateQuadMesh(Vector2D(0, 0), Vector2D(0, 0));

	Gdiplus::Bitmap textureBitmap = Gdiplus::Bitmap(64, 64);
	Gdiplus::Rect textureRect = Gdiplus::Rect(0, 0, 512, 512);
	texture->CreateTextureFromFile("Monkey.png");
	
	spriteSource = new SpriteSource(3,5,texture);
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;
	currentHealth = maxHealth;

	sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
}

void Levels::Level2::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	//std::cout << "Level2::Update" << std::endl;
	sprite->Draw();

	/*currentHealth--;
	if (currentHealth == 0) {
		lives--;
		if (lives == 0) {
			Engine::GetInstance().Stop();
		} else {
			GetSpace()->RestartLevel();
		}
	}*/
}

void Levels::Level2::Shutdown()
{
	std::cout << "Level2::Shutdown" << std::endl;
	delete sprite;
	sprite = nullptr;
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;
	delete spriteSource;
	spriteSource = nullptr;
	mesh = nullptr;
	texture = nullptr;
}
