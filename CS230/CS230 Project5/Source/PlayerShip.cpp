//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerShip.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Space.h"
#include <Graphics.h>
#include <Input.h>
//#include "SoundManager.h"
#include <Engine.h>
#include <Collider.h>
#include <GameObjectManager.h>
#include "BulletMovement.h"
#include <Sprite.h>
#include "Omega.h"

void Behaviors::CollisionHandlerShip(GameObject & ship, GameObject & otherObject)
{
	if (otherObject.GetName() == "Asteroid") {
		//deal damage to the asteroid
		GameObject::DealDamage(otherObject, ship, 1);
		//deal damage to our ship
		GameObject::DealDamage(ship, otherObject, 100);
	}
}

void Behaviors::DamageHandlerShip(int ammount, std::string type, GameObject & damageCauser, GameObject & damageTaker)
{
	UNREFERENCED_PARAMETER(damageCauser);
	UNREFERENCED_PARAMETER(ammount);

	damageTaker.setHealth(0);

	damageTaker.GetComponent<Behaviors::PlayerShip>()->PlayDeathSequence();

	damageTaker.GetComponent<Collider>()->Disable();
}

Behaviors::PlayerShip::PlayerShip(float _forwardThrust, float _maximumSpeed, float _rotationSpeed, float _deathDuration) : Component("PlayerShip")
{
	// Movement properties
	forwardThrust = _forwardThrust;
	maximumSpeed = _maximumSpeed;
	rotationSpeed = _rotationSpeed;
	deathDuration = _deathDuration;

	// Components
	transform = nullptr;
	physics = nullptr;
	sprite = nullptr;

	//other
	//soundEvent = nullptr;

	// Other variables
	timer = 0;
	counter = 0;
	isDying = false;
	score = 0;
}

Component * Behaviors::PlayerShip::Clone() const
{
	return new PlayerShip(forwardThrust, maximumSpeed, rotationSpeed, deathDuration);
}

void Behaviors::PlayerShip::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
	physics = GetOwner()->GetComponent<Physics>();
	sprite = GetOwner()->GetComponent<Sprite>();

	GetOwner()->GetComponent<Collider>()->SetCollisionHandler(CollisionHandlerShip);
	GetOwner()->setDamageHandler(DamageHandlerShip);

	/*soundEvent = Engine::GetInstance().GetModule<SoundManager>()->PlayEvent("Test Tones");
	soundEvent->setPaused(true);
	soundEvent->setVolume(0.5f);
	soundEvent->setParameterValue("Wave Type", 0);
	soundEvent->setParameterValue("LowMidHigh", 0);*/
}

void Behaviors::PlayerShip::Update(float dt)
{
	if (!isDying) {
		Move();
		Rotate();

		if (Input::GetInstance().CheckReleased(' ')) {
			Shoot();
		}

		if (Input::GetInstance().CheckReleased('T')) {
			//Engine::GetInstance().GetModule<SoundManager>()->PlaySound("teleport.wav");
			Teleport();
		}
	}
	else {
		timer += dt;

		physics->SetAngularVelocity(4.5f);

		if (counter % 2 == 0) {
			startAlpha = 1.0f;
			endAlpha = 0.05f;
		}
		else
		{
			startAlpha = 0.05f;
			endAlpha = 1.0f;
		}

		float percent = timer / 0.45f;
		float alpha = startAlpha + percent * (endAlpha - startAlpha);

		sprite->SetAlpha(alpha);

		if (timer > 0.45f)
		{
			timer = 0;
			counter++;
		}

		if (counter > 4) {
			//restart the game
			GetOwner()->GetSpace()->SetLevel<Levels::Omega>();
		}
	}
	
}

void Behaviors::PlayerShip::Serialize(Parser & parser) const
{
	UNREFERENCED_PARAMETER(parser);
}

void Behaviors::PlayerShip::Deserialize(Parser & parser)
{
	UNREFERENCED_PARAMETER(parser);
}

unsigned Behaviors::PlayerShip::GetScore() const
{
	return score;
}

void Behaviors::PlayerShip::IncreaseScore(unsigned amount)
{
	score += amount;
}

void Behaviors::PlayerShip::Move() const
{
	//const float speed = 15.0f;
	if (Input::GetInstance().IsKeyDown('W')) {
		Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

		Vector2D force = MousePos - transform->GetTranslation();

		force = force.Normalized();

		physics->AddForce(force * forwardThrust);

		//soundEvent->setPaused(false);
	} else {
		//soundEvent->setPaused(true);
	}
}

void Behaviors::PlayerShip::Rotate() const
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	transform->LookAt(MousePos);
}

void Behaviors::PlayerShip::Shoot()
{
	GameObject* newBullet = new GameObject(*GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet"));

	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	Vector2D force = MousePos - transform->GetTranslation();

	force = force.Normalized();

	newBullet->GetComponent<Bullet>()->SetDirection(force);

	newBullet->GetComponent<Transform>()->SetTranslation(transform->GetTranslation());
	newBullet->GetComponent<Transform>()->SetRotation(transform->GetRotation());

	GetOwner()->GetSpace()->GetObjectManager().AddObject(*newBullet);
}

void Behaviors::PlayerShip::Teleport()
{
	Vector2D MousePos = Graphics::GetInstance().ScreenToWorldPosition(Input::GetInstance().GetCursorPosition());

	transform->SetTranslation(MousePos);
}

void Behaviors::PlayerShip::PlayDeathSequence()
{
	isDying = true;
}


