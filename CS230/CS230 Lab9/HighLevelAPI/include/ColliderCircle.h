//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.h
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderCircle : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for circle collider.
	ColliderCircle(float radius = 50.0f);

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Get the circle collider's radius.
	// Returns:
	//	 The circle collider's radius.
	float GetRadius() const;

	// Set the circle collider's radius.
	// Params:
	//   radius = The circle collider's new radius.
	void SetRadius(float radius);

	// Check for collision between a circle and another arbitrary collider.
	// Params:
	//	 other = Reference to the second circle collider component.
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

	// Radius of the circle collider.
	float radius;
};

//------------------------------------------------------------------------------
