//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"

#include "EventManager.h" // Event
#include <set>	// std::set

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;
class Sprite;
struct LineSegment;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

typedef enum ColliderType
{
	ColliderTypeCircle,
	ColliderTypeLine,
	ColliderTypeRectangle,
	ColliderTypeTilemap,
} ColliderType;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Collision event - Generated when two objects collide
struct CollisionEvent : public Event
{
	CollisionEvent(GameObject& otherObject, const std::string& type = "CollisionPersisted");
	GameObject& otherObject;
};

// Collider class - Detects collisions between objects
class Collider : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new collider component.
	// Params:
	//   owner = Reference to the object that owns this component.
	Collider(ColliderType type);

	// Set component pointers.
	void Initialize() override;

	// Logic update for this component with fixed timestep.
	void FixedUpdate(float dt) override;

	// Check if two objects are colliding and send collision events.
	// Params:
	//	 other = Reference to the second collider component.
	void CheckCollision(const Collider& other);

	// Perform intersection test between two arbitrary colliders.
	// Params:
	//	 other = Reference to the second collider component.
	virtual bool IsCollidingWith(const Collider& other) const = 0;

	// Perform intersection test with ray.
	// Params:
	//   ray = The ray with which to test intersection.
	//   t   = The t value for the intersection.
	virtual bool IsIntersectingWith(const LineSegment& ray, float& t) const = 0;

	// Get the type of this component.
	ColliderType GetType() const;

	// Has this component been checked for collisons?
	bool WasProcesed() const;

	// Set this collider's processed bool.
	void SetProcessed(bool value);

protected:
	// Component pointers
	Transform* transform;
	Physics* physics;
	Sprite* sprite;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The type of collider used by this component.
	// (Currently, Circle or Line).
	ColliderType type;

	// Whether the collider has been checked for collisions this frame.
	bool processed;

	// IDs of objects this collider is colliding with
	std::set<GUID> collidersPrevious;
	std::set<GUID> collidersCurrent;
};

//------------------------------------------------------------------------------
