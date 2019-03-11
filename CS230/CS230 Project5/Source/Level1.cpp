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

//NOTE : Sound Stuff is commented out to save in upload size when submiting

#include "stdafx.h"
#include "Space.h"
#include "Level1.h"

//Other Levels
#include "Level2.h"
#include "Level3.h"

//Components
#include "PlayerShip.h"
#include "ScreenWrap.h"
#include "BulletMovement.h"
#include "TimedDeath.h"

//Resources
#include <Mesh.h>
#include <Color.h>

//Systems
#include <GameObjectFactory.h>
#include <ResourceManager.h>
#include <System.h>
#include <Input.h>
#include <MeshHelper.h>
//#include <SoundManager.h>

Levels::Level1::Level1() : Level("Level1")
{
	/*// Sound manager
	soundManager = nullptr;
	musicChannel = nullptr;*/
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::TimedDeath>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::Bullet>();

	GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet"));

	/*Mesh* meshShip = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	meshShip->SetName("meshShip");
	ResourceManager::GetInstance().AddMesh(meshShip);*/

	/*soundManager = Engine::GetInstance().GetModule<SoundManager>();
	soundManager->AddMusic("Asteroid_Field.mp3");
	soundManager->AddEffect("teleport.wav");

	soundManager->AddBank("Master Bank.strings.bank");
	soundManager->AddBank("Master Bank.bank");*/
}

void Levels::Level1::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerShip>();

	GameObject* Ship = GameObjectFactory::GetInstance().CreateObject("Ship");
	GetSpace()->GetObjectManager().AddObject(*Ship);

	GameObject* text = GameObjectFactory::GetInstance().CreateObject("Text");
	GetSpace()->GetObjectManager().AddObject(*text);

	//musicChannel = soundManager->PlaySound("Asteroid Field");
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	/*if (Input::GetInstance().CheckReleased('T')) {
		soundManager->PlaySound("teleport.wav");
	}*/

	if (Input::GetInstance().CheckReleased('1')) {
		GetSpace()->RestartLevel();
	}
	else if (Input::GetInstance().CheckReleased('2'))
	{
		GetSpace()->SetLevel<Levels::Level2>();
	}
	else if (Input::GetInstance().CheckReleased('3')) {
		GetSpace()->SetLevel<Levels::Level3>();
	}
}

void Levels::Level1::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	/*musicChannel->stop();
	musicChannel = nullptr;*/
}

void Levels::Level1::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;

	ResourceManager::GetInstance().Shutdown();

	//soundManager->Shutdown();
}