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

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Collider.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderRectangle : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for rectangle collider.
	// Params:
	//   extents = The rectangle's extents (half-width, half-height).
	ColliderRectangle(const Vector2D& extents = Vector2D(50.0f, 50.0f));

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Get the rectangle collider's extents (half-width, half-height).
	// Returns:
	//	 The extents of the rectangle.
	const Vector2D& GetExtents() const;

	// Set the rectangle collider's extents (half-width, half-height).
	// Params:
	//   extents = The new extents of the rectangle.
	void SetExtents(const Vector2D& extents);

	// Check for collision between a rectangle and another arbitrary collider.
	// Params:
	//	 other = Reference to the second collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

	// Perform intersection test with ray.
	// Params:
	//   ray = The ray with which to test intersection.
	//   t   = The t value for the intersection.
	bool IsIntersectingWith(const LineSegment& ray, float& t) const override;

	// Save object data to file.
	// Params:
	//   parser = The parser object used to save the object's data.
	void Serialize(Parser& parser) const;

	// Load object data from file
	// Params:
	//   parser = The parser object used to load the object's data.
	void Deserialize(Parser& parser);

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Extents of the rectangle collider.
	Vector2D extents;
};

//------------------------------------------------------------------------------
