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

//NOTE : Sound Stuff is commented out to save in upload size when submiting

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
#include "Asteroid.h"
#include <SpriteText.h>
#include <Transform.h>
#include <Physics.h>

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
//#include <SoundManager.h>
#include <Random.h>

Levels::Omega::Omega() : Level("Omega")
{
	/*// Sound manager
	soundManager = nullptr;
	musicChannel = nullptr;*/

	timer = 0;
}

void Levels::Omega::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	//Register Custom Components
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::TimedDeath>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::Bullet>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerShip>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::Asteroid>();

	GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet"));

	GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Asteroid"));

	/*//Setup Sounds
	soundManager = Engine::GetInstance().GetModule<SoundManager>();
	soundManager->AddMusic("Asteroid_Field.mp3");
	soundManager->AddEffect("teleport.wav");

	soundManager->AddBank("Master Bank.strings.bank");
	soundManager->AddBank("Master Bank.bank");*/
}

void Levels::Omega::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	//arena setup
	GameObject* walls = GameObjectFactory::GetInstance().CreateObject("Walls");
	GetSpace()->GetObjectManager().AddObject(*walls);

	GameObject* Line = GameObjectFactory::GetInstance().CreateObject("Line");
	GetSpace()->GetObjectManager().AddObject(*Line);

	GameObject* text = GameObjectFactory::GetInstance().CreateObject("ScoreText");
	scoreText = text->GetComponent<SpriteText>();
	GetSpace()->GetObjectManager().AddObject(*text);

	GameObject* instructionText = GameObjectFactory::GetInstance().CreateObject("Instructions");
	GetSpace()->GetObjectManager().AddObject(*instructionText);

	GameObject* Ship = GameObjectFactory::GetInstance().CreateObject("Ship");
	playerShip = Ship->GetComponent<Behaviors::PlayerShip>();
	GetSpace()->GetObjectManager().AddObject(*Ship);

	/*//play background music
	musicChannel = soundManager->PlaySound("Asteroid Field");*/
}

void Levels::Omega::Update(float dt)
{
	timer -= dt;

	if (timer < 0) {
		SpawnAsteroid();
		timer = RandomRange(0.2f, 3.0f);
	}

	UpdateScore();
}

void Levels::Omega::SpawnAsteroid(void)
{
	GameObject* newAsteroid = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Asteroid"));

	newAsteroid->GetComponent<Transform>()->SetTranslation(Vector2D(RandomRange(-500.0f, 500.0f), 400));

	Behaviors::Asteroid* asteroidComp = newAsteroid->GetComponent<Behaviors::Asteroid>();

	newAsteroid->GetComponent<Physics>()->SetVelocity(Vector2D(asteroidComp->getRandStrafeSpeed(), -asteroidComp->getRandSpeed()));

	GetSpace()->GetObjectManager().AddObject(*newAsteroid);
}

void Levels::Omega::UpdateScore()
{
	std::string scoreString = "Score : " + std::to_string(playerShip->GetScore());
	scoreText->SetText(scoreString);
}

void Levels::Omega::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	/*musicChannel->stop();
	musicChannel = nullptr;*/
}

void Levels::Omega::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	ResourceManager::GetInstance().Shutdown();

	//soundManager->Shutdown();
}