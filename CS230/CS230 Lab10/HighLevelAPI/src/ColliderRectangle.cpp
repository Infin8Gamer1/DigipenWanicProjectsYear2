//------------------------------------------------------------------------------
//
// File Name:	ColliderRectangle.h
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
#include "ColliderRectangle.h"

// Math
#include "Intersection2D.h" // Circle collision
#include "Vertex.h"			// constructors

// Systems
#include "DebugDraw.h"	// AddCircle
#include "Space.h"		// GetCamera
#include "Graphics.h"	// SetTransform
#include "Parser.h"

// Components
#include "GameObject.h" // GetTransform
#include "Transform.h"	// GetTranslation
#include "ColliderCircle.h"	// GetRadius

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor for circle collider.
// Params:
//   extents = The rectangle's extents (half-width, half-height).
ColliderRectangle::ColliderRectangle(const Vector2D& extents)
	: Collider(ColliderTypeRectangle), extents(extents)
{
}

// Clone an collider and return a pointer to the cloned object.
// Returns:
//   A pointer to a collider.
Component* ColliderRectangle::Clone() const
{
	return new ColliderRectangle(*this);
}

// Debug drawing for colliders.
void ColliderRectangle::Draw()
{
	Camera& camera = Graphics::GetInstance().GetDefaultCamera();
	DebugDraw::GetInstance().AddRectangle(transform->GetTranslation(), extents, camera, Colors::Green);
}

// Get the rectangle collider's extents (half-width, half-height).
// Returns:
//	 The extents of the rectangle.
const Vector2D& ColliderRectangle::GetExtents() const
{
	return extents;
}

// Set the rectangle collider's extents (half-width, half-height).
// Params:
//   extents = The new extents of the rectangle.
void ColliderRectangle::SetExtents(const Vector2D& extents_)
{
	extents = extents_;
}

// Check for collision between a circle and an arbitrary collider.
// Params:
//	 other = Reference to the second circle collider component.
bool ColliderRectangle::IsCollidingWith(const Collider& other) const
{
	Transform* transformOther = other.transform;
	BoundingRectangle rectangle = BoundingRectangle(transform->GetTranslation(), extents);

	switch (other.GetType())
	{
	case ColliderTypePoint:
		return PointRectangleIntersection(transformOther->GetTranslation(), rectangle);
		break;
	case ColliderTypeRectangle:
	{
		const Vector2D& extentsOther = static_cast<const ColliderRectangle&>(other).extents;
		return RectangleRectangleIntersection(rectangle, BoundingRectangle(transformOther->GetTranslation(), extentsOther));
		break;
	}
	case ColliderTypeCircle:
	{
		float radiusOther = static_cast<const ColliderCircle&>(other).GetRadius();
		return RectangleCircleIntersection(rectangle, Circle(transformOther->GetTranslation(), radiusOther));
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
void ColliderRectangle::Serialize(Parser& parser) const
{
	parser.WriteVariable("extents", extents);
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void ColliderRectangle::Deserialize(Parser& parser)
{
	parser.ReadVariable("extents", extents);
}
