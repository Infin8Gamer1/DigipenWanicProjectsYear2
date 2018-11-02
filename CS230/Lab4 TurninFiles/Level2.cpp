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
#include <Mesh.h>
#include <gdiplus.h>
#include <Texture.h>
#include <Engine.h>

Levels::Level2::Level2() : Level("Level2")
{
	mesh = nullptr;
	texture = nullptr;

	spriteSource = nullptr;
	columns = 3;
	rows = 5;

	sprite = nullptr;
	animation = nullptr;
	
	lives = 2;
	maxHealth = 2;
}

void Levels::Level2::Load()
{
	std::cout << "Level2::Load" << std::endl;

	Vector2D textureSize = Vector2D(1.0f / columns, 1.0f / rows);
	mesh = CreateQuadMesh(textureSize, Vector2D(1, 1));

	texture = Texture::CreateTextureFromFile("Monkey.png");
	
	spriteSource = new SpriteSource(columns, rows, texture);
}

void Levels::Level2::Initialize()
{
	std::cout << "Level2::Initialize" << std::endl;
	currentHealth = maxHealth;

	sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	animation = new Animation(sprite);
	animation->Play(0, 8, 0.0f, true);
}

void Levels::Level2::Update(float dt)
{
	animation->Update(dt);
	sprite->Draw();

	if (animation->IsDone() == false) {
		return;
	}

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
	delete sprite;
	sprite = nullptr;
	delete animation;
	animation = nullptr;
}

void Levels::Level2::Unload()
{
	std::cout << "Level2::Unload" << std::endl;
	delete spriteSource;
	spriteSource = nullptr;
	delete mesh;
	mesh = nullptr;
	delete texture;
	texture = nullptr;
}
