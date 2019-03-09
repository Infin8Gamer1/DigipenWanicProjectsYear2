//------------------------------------------------------------------------------
//
// File Name:	BulletMovement.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BulletMovement.h"
#include "Physics.h"
#include "GameObject.h"
#include <Parser.h>
#include <Collider.h>


void Behaviors::CollisionHandlerBullet(GameObject & bullet, GameObject & other)
{
	if (other.GetName() == "Asteroid") {
		GameObject::DealDamage(other, bullet, bullet.GetComponent<Bullet>()->damage);

		bullet.Destroy();
	}
}

Behaviors::Bullet::Bullet() : Component("Bullet")
{
	forceDirection = Vector2D(0, 1);
	speed = 20.0;
	damage = 0;
}

Behaviors::Bullet::Bullet(Vector2D Direction, float Speed, int Damage) : Component("Bullet")
{
	forceDirection = Direction;
	speed = Speed;
	damage = Damage;
}

Component * Behaviors::Bullet::Clone() const
{
	return new Bullet(forceDirection, speed, damage);
}

void Behaviors::Bullet::Deserialize(Parser & parser)
{
	parser.ReadVariable("speed", speed);
	parser.ReadVariable("damage", damage);
}

void Behaviors::Bullet::Serialize(Parser & parser) const
{
	parser.WriteVariable("speed", speed);
	parser.WriteVariable("damage", damage);
}

void Behaviors::Bullet::Initialize()
{
	GetOwner()->GetComponent<Physics>()->SetVelocity(forceDirection * speed);

	GetOwner()->GetComponent<Collider>()->SetCollisionHandler(CollisionHandlerBullet);
}

void Behaviors::Bullet::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void Behaviors::Bullet::SetSpeed(float Speed)
{
	speed = Speed;
}

void Behaviors::Bullet::SetDirection(Vector2D Direction)
{
	forceDirection = Direction;
}