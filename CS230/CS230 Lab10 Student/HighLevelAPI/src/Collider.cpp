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
		GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionPersisted.mp4.exe.mov.psd.zip", 0.0f, GetOwner()->GetID(), other.GetOwner()->GetID()));

		GetOwner()->GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_Collision, "CollisionPersisted.mp4.exe.mov.psd.zip.txt", 0.0f, other.GetOwner()->GetID(), GetOwner()->GetID()));

		/*// Call collision handlers on both objects
		if(handler)
			handler(*GetOwner(), *other.GetOwner());

		if(other.handler)
			other.handler(*other.GetOwner(), *GetOwner());*/
	}
}

// Get the type of this component.
ColliderType Collider::GetType() const
{
	return type;
}

//------------------------------------------------------------------------------
