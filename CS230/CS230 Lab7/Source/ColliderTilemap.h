//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.h
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
// Forward Declarations:
//------------------------------------------------------------------------------

class Tilemap;
struct BoundingRectangle;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Enum for sides of bounding rectangle
enum RectangleSide
{
	SideBottom,
	SideTop,
	SideLeft,
	SideRight,

	// Number of sides
	SideCount,
};

// Tilemap collider class - goes on Tilemap object
class ColliderTilemap : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for Tilemap collider.
	ColliderTilemap();

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const override;

	// Debug drawing for colliders.
	void Draw() override;

	// Check for collision between a tilemap and another arbitrary collider.
	// Params:
	//	 other = Reference to the second collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

	// Sets the tilemap to use for this collider.
	// Params:
	//   map = A pointer to the tilemap resource.
	void SetTilemap(const Tilemap* map);

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Checks whether the specified side of a given rectangle is colliding with the tilemap.
	// Params:
	//   rectangle = The bounding rectangle for an object.
	//   side = The side that needs to be tested for collision.
	// Returns:
	//   True if there is a collision, false otherwise.
	bool IsSideColliding(const BoundingRectangle& rectangle, RectangleSide side) const;

	// Determines whether a point is within a collidable cell in the tilemap.
	// Params:
	//   x = The x component of the point, in world coordinates.
	//   y = The y component of the point, in world coordinates.
	// Returns:
	//   -1 if the point is outside the map, 0 if the map is empty at that position, 
	//   or a positive integer if there is a tile at that position.
	bool IsCollidingAtPosition(float x, float y) const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The tilemap
	const Tilemap* map;
};

//------------------------------------------------------------------------------
