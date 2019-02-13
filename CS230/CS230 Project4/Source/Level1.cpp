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
#include "Level3.h"
#include "Space.h"
#include "MeshHelper.h"
#include <Input.h>
#include <Mesh.h>
#include <Color.h>
#include <Engine.h>
#include <GameObjectFactory.h>
#include "PlayerShip.h"
#include <ResourceManager.h>
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

	Mesh* meshShip = CreateTriangleMesh(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1));
	meshShip->SetName("meshShip");
	ResourceManager::GetInstance().AddMesh(meshShip);

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

	GameObject* Ship = GameObjectFactory::GetInstance().CreateObject("Ship", ResourceManager::GetInstance().GetMesh("meshShip"));
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
		GetSpace()->SetLevel(new Levels::Level3());
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