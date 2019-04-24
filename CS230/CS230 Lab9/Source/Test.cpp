//------------------------------------------------------------------------------
//
// File Name:	Test.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Test.h"

// Systems
#include <SpaceManager.h> // AddSpace, Space::SetLevel
#include <Engine.h>		  // GetModule
#include <GameObjectFactory.h>
#include <Graphics.h>	// GetCameraPosition
#include <Input.h>		// CheckTriggered
#include <GameObjectManager.h> // Add
#include <Camera.h>		// SetCameraPosition

// Resources
#include <SpriteSource.h>
#include <PostEffect.h>
#include "FadeToBlack.h"
#include "ColorInverter.h"
#include "Vignette.h"
#include "Noise.h"
#include "Scanline.h"

// Components
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Reactive.h"
#include "ColliderRectangle.h"
#include "ColliderCircle.h"
#include "Physics.h"
#include <SpriteText.h>

//------------------------------------------------------------------------------

namespace Levels
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create an instance of the test level state.
	Test::Test()
		: Level("Test Level"),
		hudSpace(nullptr), fadeToBlack(nullptr),
		graphics(nullptr), input(nullptr)
	{
	}

	// Load the resources associated with the MainMenu game state.
	void Test::Load()
	{
		// Effects
		fadeToBlack = new Effects::FadeToBlack();
		invertColors = new Effects::ColorInverter();
		vignette = new Effects::Vignette();
		noise = new Effects::Noise();
		scanline = new Effects::Scanline();
		graphics = &Graphics::GetInstance();


		// Set Beta Framework’s background color to black
		graphics->SetBackgroundColor(Colors::Black);

		// Create HUD Space
		Engine& engine = Engine::GetInstance();
		hudSpace = engine.GetModule<SpaceManager>()->AddSpace("HudSpace", true);
		Camera& hudCamera = hudSpace->GetCamera();
		hudCamera.SetProjectionMode(PM_Perspective);
		hudCamera.SetFOV(120.0f);

		// Enable perspective for default camera
		Camera& defaultCamera = GetSpace()->GetCamera();
		defaultCamera.SetProjectionMode(PM_Perspective);
		defaultCamera.SetFOV(120.0f);

		// Input
		input = &Input::GetInstance();
	}

	// Initialize the memory associated with the MainMenu game state.
	void Test::Initialize()
	{
		// Background
		GetSpace()->GetObjectManager().AddObject(
			*GameObjectFactory::GetInstance().CreateObject("Background", GetSpace()));

		GameObject* textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		SpriteText* textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("Wacky");
		textComponent->SetColor(Colors::Red);
		textComponent->SetZDepth(1.0f);
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(0, 1.5));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("Effects");
		textComponent->SetColor(Colors::Blue);
		textComponent->SetZDepth(0.25f);
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(0, -1));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("F To Fade");
		textComponent->SetColor(Colors::Red);
		textComponent->SetZDepth(0.1f);
		textObject->GetComponent<Transform>()->SetScale(Vector2D(0.3f, 0.3f));
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(-2, 0));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("V for Vignette");
		textComponent->SetColor(Colors::Green);
		textComponent->SetZDepth(0.1f);
		textObject->GetComponent<Transform>()->SetScale(Vector2D(0.3f, 0.3f));
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(2, 1));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("I to Inverse");
		textComponent->SetColor(Colors::Orange);
		textComponent->SetZDepth(0.05f);
		textObject->GetComponent<Transform>()->SetScale(Vector2D(0.3f, 0.3f));
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(2, 0));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("N For Noise");
		textComponent->SetColor(Colors::Aqua);
		textComponent->SetZDepth(0.1f);
		textObject->GetComponent<Transform>()->SetScale(Vector2D(0.3f, 0.3f));
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(-2, 1));
		GetSpace()->GetObjectManager().AddObject(*textObject);

		textObject = GameObjectFactory::GetInstance().CreateObject("Text", GetSpace());
		textComponent = textObject->GetComponent<SpriteText>();
		textComponent->SetText("L for ScanLines");
		textComponent->SetColor(Colors::Grey);
		textComponent->SetZDepth(0.02f);
		textObject->GetComponent<Transform>()->SetScale(Vector2D(0.3f, 0.3f));
		textObject->GetComponent<Transform>()->SetTranslation(Vector2D(-3, 0.5));
		GetSpace()->GetObjectManager().AddObject(*textObject);
	}

	// Update the MainMenu game state.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Test::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// Move the camera based on user input
		MoveCamera(dt);

#pragma region FadeToBlack
		// If the user presses the 'F' key, fade out.
		if (input->CheckTriggered('F'))
		{
			if (!fadeToBlack->IsActive())
			{
				graphics->PushEffect(*fadeToBlack);
			}
			else
			{
				graphics->RemoveEffect(*fadeToBlack);
			}
		}

		// Is the fade effect active?
		if (fadeToBlack->IsActive())
		{
			fadeToBlack->Update(dt);
		}
#pragma endregion

#pragma region InvertColors
		// If the user presses the 'I' key, invert colors.
		if (input->CheckTriggered('I'))
		{
			if (!invertColors->IsActive())
			{
				graphics->PushEffect(*invertColors);
			}
			else
			{
				graphics->RemoveEffect(*invertColors);
			}
		}

		// Is the fade effect active?
		if (invertColors->IsActive())
		{
			invertColors->Update(dt);
		}
#pragma endregion

#pragma region Vignette
		// If the user presses the 'V' key, Turn on Vignette.
		if (input->CheckTriggered('V'))
		{
			if (!vignette->IsActive())
			{
				graphics->PushEffect(*vignette);
			}
			else
			{
				graphics->RemoveEffect(*vignette);
			}
		}

		// Is the fade effect active?
		if (vignette->IsActive())
		{
			vignette->Update(dt);
		}
#pragma endregion

#pragma region Noise
		// If the user presses the 'N' key, noise time.
		if (input->CheckTriggered('N'))
		{
			if (!noise->IsActive())
			{
				graphics->PushEffect(*noise);
			}
			else
			{
				graphics->RemoveEffect(*noise);
			}
		}

		// Is the fade effect active?
		if (noise->IsActive())
		{
			noise->Update(dt);
		}
#pragma endregion

#pragma region ScanLines
		// If the user presses the 'L' key, Scan Lines ON.
		if (input->CheckTriggered('L'))
		{
			if (!scanline->IsActive())
			{
				graphics->PushEffect(*scanline);
			}
			else
			{
				graphics->RemoveEffect(*scanline);
			}
		}

		// Is the fade effect active?
		if (scanline->IsActive())
		{
			scanline->Update(dt);
		}
#pragma endregion

	}

	// Unload the resources associated with the MainMenu game state.
	void Test::Unload()
	{
		// Destroy the space we created earlier
		hudSpace->Destroy();

		// Remove all existing effects from graphics
		graphics->ClearEffects();

		// We created the effects, so we have to destroy them as well
		delete fadeToBlack;

		delete invertColors;

		delete vignette;

		delete noise;

		delete scanline;
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Move the camera based on user input
	void Test::MoveCamera(float dt)
	{
		float moveSpeed = 3.0f;
		float zoomSpeed = 10.0f;
		Camera& spaceCamera = GetSpace()->GetCamera();
		Vector2D cameraPos = spaceCamera.GetTranslation();
		float cameraZoom = spaceCamera.GetFOV();

		// Move camera
		if (input->CheckHeld('W'))
			cameraPos.y += moveSpeed * dt;

		if (input->CheckHeld('S'))
			cameraPos.y -= moveSpeed * dt;

		if (input->CheckHeld('D'))
			cameraPos.x += moveSpeed * dt;

		if (input->CheckHeld('A'))
			cameraPos.x -= moveSpeed * dt;

		// Zoom out
		if (input->CheckHeld('Q'))
			cameraZoom += zoomSpeed * dt;

		// Zoom in
		if (input->CheckHeld('E'))
			cameraZoom -= zoomSpeed * dt;

		spaceCamera.SetTranslation(cameraPos);
		spaceCamera.SetFOV(cameraZoom);
	}
}
