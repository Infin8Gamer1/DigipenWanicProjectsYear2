//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MonkeyMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Animation.h"
#include <Graphics.h>
#include <Input.h>

Behaviors::MonkeyMovement::MonkeyMovement() : Component("MonkeyMovement")
{
	// Components
	transform = nullptr;
	physics = nullptr;
	animation = nullptr;
}

Component * Behaviors::MonkeyMovement::Clone() const
{
	return new MonkeyMovement();
}

void Behaviors::MonkeyMovement::Initialize()
{
	//get Components
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
}

void Behaviors::MonkeyMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	//call movement code
	Move();

	//basic collision handeling
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
	}
	else {
		isFlying = true;

		if (animation->IsDone()) {
			animation->Play(9, 1, 0.1f, false);
		}
	}

	
}

void Behaviors::MonkeyMovement::Move() const
{
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

void Behaviors::MonkeyMapCollisionHandler(GameObject & object, MapCollision collision)
{
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(collision);
}
