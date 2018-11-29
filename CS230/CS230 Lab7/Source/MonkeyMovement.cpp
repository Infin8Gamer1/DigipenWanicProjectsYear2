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
	onGround = false;

	//get Components
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
	//set the collision handler for the monkey
	static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(MonkeyMapCollisionHandler);
}

void Behaviors::MonkeyMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	//call movement code
	MoveVertical();
	MoveHorizontal();

	//do animations
	if (onGround) {
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
		if (animation->IsDone()) {
			animation->Play(9, 1, 0.1f, false);
		}
	}

	
}

void Behaviors::MonkeyMovement::MoveHorizontal() const
{
	//left
	if (Input::GetInstance().IsKeyDown('A')) {
		physics->AddForce(Vector2D(-1, 0) * strafeForce);
	}
	//right
	if (Input::GetInstance().IsKeyDown('D')) {
		physics->AddForce(Vector2D(1, 0) * strafeForce);
	}
}

void Behaviors::MonkeyMovement::MoveVertical()
{
	//jump
	if (Input::GetInstance().IsKeyDown(' ') && onGround) {
		physics->AddForce(Vector2D(0, 1) * jumpForce);
		onGround = false;
	}

	if (physics->GetVelocity().y < -0.5) {
		onGround = false;
	}
}

void Behaviors::MonkeyMapCollisionHandler(GameObject & object, MapCollision collision)
{
	if (collision.bottom) {
		static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->onGround = true;
	}
}
