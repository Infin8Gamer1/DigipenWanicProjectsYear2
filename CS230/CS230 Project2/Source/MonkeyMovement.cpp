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
	// Movement properties
	monkeyWalkSpeed = 0.0f;
	monkeyJumpSpeed = 0.0f;
	groundHeight = 0.0f;

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
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
}

void Behaviors::MonkeyMovement::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

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
	}
	else {
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

void Behaviors::MonkeyMovement::MoveHorizontal() const
{
}

void Behaviors::MonkeyMovement::MoveVertical() const
{
}
