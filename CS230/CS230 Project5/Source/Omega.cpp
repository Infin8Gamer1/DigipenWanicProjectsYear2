//------------------------------------------------------------------------------
//
// File Name:	Omega.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Space.h>
#include "Omega.h"

//Other Levels
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

//Components
#include "PlayerShip.h"
#include "ScreenWrap.h"
#include "BulletMovement.h"
#include "TimedDeath.h"
#include <SpriteText.h>
#include <Transform.h>

//Resources
#include <Mesh.h>
#include <Color.h>

//Systems
#include <GameObjectFactory.h>
#include <ResourceManager.h>
#include <System.h>
#include <Input.h>
#include <MeshHelper.h>
#include <Engine.h>
#include <SoundManager.h>

Levels::Omega::Omega() : Level("Omega")
{
	// Sound manager
	soundManager = nullptr;
	musicChannel = nullptr;
}

void Levels::Omega::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	//Register Custom Components
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::TimedDeath>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::BulletMovement>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerShip>();

	GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet"));

	//Setup Sounds
	soundManager = Engine::GetInstance().GetModule<SoundManager>();
	soundManager->AddMusic("Asteroid_Field.mp3");
	soundManager->AddEffect("teleport.wav");

	soundManager->AddBank("Master Bank.strings.bank");
	soundManager->AddBank("Master Bank.bank");
}

void Levels::Omega::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	GameObject* Ship = GameObjectFactory::GetInstance().CreateObject("Ship");
	playerShip = Ship->GetComponent<Behaviors::PlayerShip>();
	GetSpace()->GetObjectManager().AddObject(*Ship);

	GameObject* text = GameObjectFactory::GetInstance().CreateObject("ScoreText");
	scoreText = text->GetComponent<SpriteText>();
	GetSpace()->GetObjectManager().AddObject(*text);

	Line = GameObjectFactory::GetInstance().CreateObject("Line");
	GetSpace()->GetObjectManager().AddObject(*Line);

	//play background music
	musicChannel = soundManager->PlaySound("Asteroid Field");
}

void Levels::Omega::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (Input::GetInstance().CheckReleased('T')) {
		soundManager->PlaySound("teleport.wav");
	}

	//Line->GetComponent<Transform>()->SetTranslation(Line->GetComponent<Transform>()->GetTranslation() + Vector2D(0.01f, 0));

	SwitchLevels();
	UpdateScore();
}

void Levels::Omega::SpawnAsteroid(void)
{
}

void Levels::Omega::SpawnAsteroidWave(void)
{
}

void Levels::Omega::UpdateScore()
{
	std::string scoreString = "Score : " + std::to_string(playerShip->GetScore());
	scoreText->SetText(scoreString);
}

void Levels::Omega::SwitchLevels()
{
	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel<Levels::Level2>();
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel(new Levels::Level3());
	}
}

void Levels::Omega::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	musicChannel->stop();
	musicChannel = nullptr;
}

void Levels::Omega::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	ResourceManager::GetInstance().Shutdown();

	soundManager->Shutdown();
}