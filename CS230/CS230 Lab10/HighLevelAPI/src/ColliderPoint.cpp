//------------------------------------------------------------------------------
//
// File Name:	ColliderPoint.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderPoint.h"

// Math
#include "Intersection2D.h" // Circle collision

// Resources
#include "Vertex.h" // constructors

// Systems
#include "Graphics.h"  // GetDefaultCamera
#include "DebugDraw.h" // AddCircle

// Components
#include "GameObject.h" // GetTransform
#include "Transform.h"  // GetTranslation

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a point collider component.
ColliderPoint::ColliderPoint()
	: Collider(ColliderTypePoint)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component * ColliderPoint::Clone() const
{
	return new ColliderPoint(*this);
}

// Debug drawing for colliders.
void ColliderPoint::Draw()
{
	Camera& camera = Graphics::GetInstance().GetDefaultCamera();
	DebugDraw::GetInstance().AddCircle(transform->GetTranslation(), 10.0f, camera, Colors::Green);
}

// Check for collision between a circle and an arbitrary collider.
// Params:
//	 other = Reference to the second circle collider component.
bool ColliderPoint::IsCollidingWith(const Collider& other) const
{
	Transform* transformOther = other.transform;

	switch (other.GetType())
	{
	case ColliderTypePoint:
		return AlmostEqual(transform->GetTranslation(), transformOther->GetTranslation());
		break;
	default:
		return other.IsCollidingWith(*this);
		break;
	}
}
