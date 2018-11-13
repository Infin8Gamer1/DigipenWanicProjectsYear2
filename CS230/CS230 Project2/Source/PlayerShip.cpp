#include "stdafx.h"
#include "PlayerShip.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include <Graphics.h>
#include <Input.h>

Behaviors::PlayerShip::PlayerShip() : Component("PlayerShip")
{
	// Movement properties
	forwardThrust = 0.0f;
	maximumSpeed = 20.0f;
	rotationSpeed = 10.0f;
	bulletSpeed = 20.0f;

	// Bullet archetype
	bulletArchetype = nullptr;

	// Components
	transform = nullptr;
	physics = nullptr;
}

Behaviors::PlayerShip::PlayerShip(float _forwardThrust, float _maximumSpeed, float _rotationSpeed, float _bulletSpeed) : Component("PlayerShip")
{
	// Movement properties
	forwardThrust = _forwardThrust;
	maximumSpeed = _maximumSpeed;
	rotationSpeed = _rotationSpeed;
	bulletSpeed = _bulletSpeed;

	// Bullet archetype
	bulletArchetype = nullptr;

	// Components
	transform = nullptr;
	physics = nullptr;
}

Component * Behaviors::PlayerShip::Clone() const
{
	return new PlayerShip(forwardThrust, maximumSpeed, rotationSpeed, bulletSpeed);
}

void Behaviors::PlayerShip::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
}

void Behaviors::PlayerShip::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Move();
	Rotate();
}

void Behaviors::PlayerShip::Move() const
{
	const float speed = 15.0f;

	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	force = force.Normalized();

	physics->AddForce(force * speed);
}

void Behaviors::PlayerShip::Rotate() const
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	transform->LookAt(MousePos);
}

void Behaviors::PlayerShip::Shoot() const
{
}
