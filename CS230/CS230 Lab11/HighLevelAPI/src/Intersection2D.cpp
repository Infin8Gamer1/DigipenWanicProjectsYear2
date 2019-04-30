//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		Project 7
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Intersection2D.h"

// Components
#include "Physics.h" // GetOldTranslation
#include "Transform.h" // GetTranslation

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Function Definitions:
//------------------------------------------------------------------------------

// Check whether a point and circle intersect.
// Params:
//  point = The point in the intersection.
//  circle = The circle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointCircleIntersection(const Vector2D & point, const Circle & circle)
{
	return CircleCircleIntersection(circle, Circle(point, 0.0f));
}

// Check whether a point and rectangle intersect.
// Params:
//  point = The point in the intersection.
//  rect  = The rectangle in the intersection.
// Returns:
//   True if intersection, false otherwise.
bool PointRectangleIntersection(const Vector2D& point, const BoundingRectangle& rect)
{
	return RectangleRectangleIntersection(rect, BoundingRectangle(point, Vector2D()));
}

// Check whether two circles intersect.
// Params:
//  circle1 = The first circle.
//  circle2 = The second circle.
// Returns:
//   True if intersection, false otherwise.
bool CircleCircleIntersection(const Circle& circle1, const Circle& circle2)
{
	// Compare distance between centers with the sum of the radii
	// (Squared distance and sum to avoid sqrt)
	float distanceSquared = circle1.center.DistanceSquared(circle2.center);
	float radiusSumSquared = (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);

	// Return result
	return distanceSquared <= radiusSumSquared;
}


// Check whether two rectangles intersect.
// Params:
//  rect1 = The first rectangle.
//	rect2 = The second rectangle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleRectangleIntersection(const BoundingRectangle & rect1, const BoundingRectangle & rect2)
{
	if (rect1.bottom > rect2.top)
		return false;
	if (rect1.top < rect2.bottom)
		return false;
	if (rect1.left > rect2.right)
		return false;
	if (rect1.right < rect2.left)
		return false;

	// All other cases eliminated, so there must be an intersection.
	return true;
}

// Check whether a rectangle and circle intersect.
// Params:
//  rect = The rectangle.
//  circle  = The circle.
// Returns:
//   True if intersection, false otherwise.
bool RectangleCircleIntersection(const BoundingRectangle & rect, const Circle & circle)
{
	// Find point on rectangle closest to circle
	Vector2D closest = circle.center;
	if (closest.x > rect.right)
		closest.x = rect.right;
	else if (closest.x < rect.left)
		closest.x = rect.left;

	if (closest.y > rect.top)
		closest.y = rect.top;
	else if (closest.y < rect.bottom)
		closest.y = rect.bottom;

	// If distance from closest point to circle center <= radius, we have an intersection
	return closest.DistanceSquared(circle.center) <= circle.radius * circle.radius;
}
