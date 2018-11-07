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
#include "Animation.h"
#include <Engine.h>
#include <Input.h>
#include <Graphics.h>

void Behaviors::UpdateShip(Transform * transform, Physics * physics)
{
	const float speed = 15.0f;

	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	force = force.Normalized();

	physics->AddForce(force * speed);

	transform->LookAt(MousePos);
}


void Behaviors::UpdateMonkey(Transform * transform, Physics * physics, Animation * animation)
{
	const float jumpForce = 5000.0f;
	const float strafeForce = 5.0f;

	bool isFlying = false;

	float groundLevel = (-Graphics::GetInstance().GetScreenWorldDimensions().extents.y) + (transform->GetScale().y / 2);

	if (transform->GetTranslation().y <= groundLevel) {
		transform->SetTranslation(Vector2D(transform->GetTranslation().x, groundLevel));
		//make sure that the verticle velocity is 0 when you are on the floor
		physics->SetVelocity(Vector2D(physics->GetVelocity().x, 0));

		isFlying = false;

		if (animation->IsDone()) {
			if (physics->GetVelocity().x >= 0) {
				animation->Play(0, 8, 0.2f, false);
			}
			if (physics->GetVelocity().x < 0) {
				animation->Play(7, 8, 0.2f, false, true);
			}
			
		}
	} else {
		isFlying = true;

		if (animation->IsDone()) {
			animation->Play(9, 1, 0.1f, false);
		}	
	}

	//jump
	if (Input::GetInstance().IsKeyDown(' ') && !isFlying) {
		physics->AddForce(Vector2D(0, 1) * jumpForce);
	}
	//left
	if (Input::GetInstance().IsKeyDown('A')) {
		physics->AddForce(Vector2D(-1, 0) * strafeForce);
	}
	//right
	if (Input::GetInstance().IsKeyDown('D')) {
		physics->AddForce(Vector2D(1, 0) * strafeForce);
	}
	
}
