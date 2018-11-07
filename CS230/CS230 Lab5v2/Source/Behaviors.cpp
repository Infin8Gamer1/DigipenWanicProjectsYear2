//------------------------------------------------------------------------------
//
// File Name:	Behaviors.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Behaviors.h"
#include "Transform.h"
#include "Physics.h"
#include <Engine.h>
#include <Input.h>
#include <Graphics.h>

void Behaviors::UpdateShip(Transform * transform, Physics * physics)
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	physics->AddForce(force * 0.05f);

	transform->LookAt(MousePos);
}



void Behaviors::UpdateMonkey(Transform * transform, Physics * physics)
{
	bool isFlying = false;

	if (transform->GetTranslation().y <= -225) {
		transform->SetTranslation(Vector2D(transform->GetTranslation().x, -225));
		isFlying = false;
	}
	else {
		isFlying = true;
	}

	//jump
	if (Input::GetInstance().CheckReleased(' ') && !isFlying) {
		physics->AddForce(Vector2D(0, 1) * 500.0f);
	}
	//left
	if (Input::GetInstance().IsKeyDown('A')) {
		physics->AddForce(Vector2D(-1, 0) * 5.0f);
	}
	//right
	if (Input::GetInstance().IsKeyDown('D')) {
		physics->AddForce(Vector2D(1, 0) * 5.0f);
	}

	////gravity
	//if (isFlying) {
	//	physics->AddForce(Vector2D(0, -9.8f));
	//}
	
	//std::cout << "IsFlying : " << isFlying;
	
}
