//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
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
#include "ColliderCircle.h"

// Math
#include "Intersection2D.h" // Circle collision

// Resources
#include "Vertex.h" // constructors

// Systems
#include "Graphics.h"  // GetDefaultCamera
#include "DebugDraw.h" // AddCircle
#include "Parser.h"

// Components
#include "GameObject.h" // GetTransform
#include "Transform.h"  // GetTranslation

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a circle collider component.
// (Hint: Make sure to initialize the ColliderType correctly.)
ColliderCircle::ColliderCircle(float radius)
	: Collider(ColliderTypeCircle), radius(radius)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component * ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

// Debug drawing for colliders.
void ColliderCircle::Draw()
{
	Camera& camera = Graphics::GetInstance().GetDefaultCamera();
	DebugDraw::GetInstance().AddCircle(transform->GetTranslation(), radius, camera, Colors::Green);
}

// Get the circle collider's radius.
// Returns:
//	 The circle collider's radius.
float ColliderCircle::GetRadius() const
{
	return radius;
}

// Set the circle collider's radius.
// Params:
//   radius = The circle collider's new radius.
void ColliderCircle::SetRadius(float radius_)
{
	radius = radius_;
}

// Check for collision between a circle and an arbitrary collider.
// Params:
//	 other = Reference to the second circle collider component.
bool ColliderCircle::IsCollidingWith(const Collider& other) const
{
	Transform* transformOther = other.transform;
	Circle circle = Circle(transform->GetTranslation(), radius);

	switch (other.GetType())
	{
	case ColliderTypePoint:
		return PointCircleIntersection(transformOther->GetTranslation(), circle);
		break;
	case ColliderTypeCircle:
	{
		float radiusOther = static_cast<const ColliderCircle&>(other).radius;
		return CircleCircleIntersection(circle,
			Circle(transformOther->GetTranslation(), radiusOther));
		break;
	}
	default:
		return other.IsCollidingWith(*this);
		break;
	}
}

// Save object data to file.
// Params:
//   parser = The parser object used to save the object's data.
void ColliderCircle::Serialize(Parser& parser) const
{
	parser.WriteVariable("radius", radius);
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void ColliderCircle::Deserialize(Parser& parser)
{
	parser.ReadVariable("radius", radius);
}
