//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"

Collider::Collider(ColliderType _type) : Component("Collider")
{
	type = _type;
}

void Collider::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
}

void Collider::CheckCollision(const Collider & other)
{
	if (IsCollidingWith(other)) {
		this->handler(*this->GetOwner(), *other.GetOwner());
		other.handler(*other.GetOwner(), *this->GetOwner());
	}
}

ColliderType Collider::GetType() const
{
	return type;
}

void Collider::SetCollisionHandler(CollisionEventHandler _handler)
{
	handler = _handler;
}
