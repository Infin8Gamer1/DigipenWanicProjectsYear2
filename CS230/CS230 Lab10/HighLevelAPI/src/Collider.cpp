//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
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
#include "Collider.h"

// Components
#include "GameObject.h" // GetComponent
#include "Transform.h" // Transform
#include "Physics.h"   // Physics
#include "Space.h"
#include "Event.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Allocate a new collider component.
// Params:
//   type = The type of collider (circle, line, etc.).
Collider::Collider(ColliderType type)
	: Component("Collider"), transform(nullptr), physics(nullptr), type(type)
{
}

// Set component pointers.
void Collider::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
	physics = GetOwner()->GetComponent<Physics>();
}

void Collider::FixedUpdate(float dt)
{
	for each (GUID x in collidersPrevious)
	{
		if (collidersCurrent.find(x) != collidersCurrent.end())
		{
			continue;
		}

		GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionEnded", 0.0f, GetOwner()->GetID(), x));

		GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionEnded", 0.0f, x, GetOwner()->GetID()));
	}

	std::swap(collidersCurrent, collidersPrevious);

	collidersCurrent.clear();
}

void Collider::Draw()
{
}

// Check if two objects are colliding and send collision events.
// Params:
//	 other = Pointer to the second collider component.
void Collider::CheckCollision(const Collider& other)
{
	// Perform the actual collision math for collisions between objects
	bool colliding = IsCollidingWith(other);

	// If they collide, call respective handlers
	if (colliding)
	{

		if (collidersPrevious.find(other.GetOwner()->GetID()) != collidersPrevious.end())
		{
			GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionPersisted", 0.0f, GetOwner()->GetID(), other.GetOwner()->GetID()));

			GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionPersisted", 0.0f, other.GetOwner()->GetID(), GetOwner()->GetID()));
		}
		else if (collidersCurrent.find(other.GetOwner()->GetID()) == collidersCurrent.end())
		{
			GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionStarted", 0.0f, GetOwner()->GetID(), other.GetOwner()->GetID()));

			GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionStarted", 0.0f, other.GetOwner()->GetID(), GetOwner()->GetID()));
		}

		collidersCurrent.insert(collidersCurrent.begin(), other.GetOwner()->GetID());
	}
}

// Get the type of this component.
ColliderType Collider::GetType() const
{
	return type;
}

//------------------------------------------------------------------------------
