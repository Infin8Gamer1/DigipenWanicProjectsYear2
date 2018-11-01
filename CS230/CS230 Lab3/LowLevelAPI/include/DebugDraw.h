//------------------------------------------------------------------------------
//
// File Name:	DebugDraw.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaEngine
// Course:		VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <vector>

#include "Shapes2D.h"
#include "Color.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class Vector2D Vector2D;
typedef class Mesh Mesh;
typedef class Camera Camera;

//------------------------------------------------------------------------------
// Class Definition:
//------------------------------------------------------------------------------

class DebugDraw
{
public:
	//------------------------------------------------------------------------------
	// Public Functions
	//------------------------------------------------------------------------------

	// Draws all debug objects. Should only be called by existing Low-Level API systems.
	void Draw();

	// Adds a line to the list of lines to be drawn. Note that actual drawing does not occur 
	// until EndLineStrip is called.
	// Params:
	//   start = The start point of the line segment.
	//   end   = The end point of the line segment.
	//   color = The color of the line. Defaults to white.
	void AddLineToStrip(const Vector2D& start, const Vector2D& end, const Color& color = Colors::White);
	void EndLineStrip(Camera& camera);
	void AddCircle(const Vector2D& center, float radius, Camera& camera, const Color& color = Colors::White);
	void AddRectangle(const Vector2D& center, const Vector2D& extents, Camera& camera, const Color& color = Colors::White);

	static DebugDraw& GetInstance();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Private to prevent accidental instantiation/destruction
	DebugDraw();
	~DebugDraw();

	DebugDraw& operator=(const DebugDraw& other) = delete;
	DebugDraw(const DebugDraw& other) = delete;

	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	struct DebugCircle
	{
		DebugCircle(const Vector2D& center, float radius, const Color& color, Camera& camera);

		Circle shape; // Shape info

		Color color; // Color for drawing

		Camera& camera; // Camera to use for drawing
	};

	struct DebugRectangle
	{
		DebugRectangle(const Vector2D& center, const Vector2D& extents, const Color& color, Camera& camera);

		BoundingRectangle shape; // Shape info

		Color color; // Color for drawing

		Camera& camera; // Camera to use for drawing
	};

	struct DebugLineSegment
	{
		DebugLineSegment(const Vector2D& start, const Vector2D& end, const Color& color);

		Vector2D start; // First point of line segment
		Vector2D end;   // Second point of line segment

		Color color; // Color of the segment
	};

	struct DebugLineStrip
	{
		DebugLineStrip(const std::vector<DebugLineSegment>& segments, Camera& camera);
		~DebugLineStrip();

		Mesh* mesh;     // The mesh used when drawing this line strip
		Camera& camera; // Camera to use for drawing
	};

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	std::vector<DebugRectangle> rectangles;
	std::vector<DebugCircle> circles;
	std::vector<DebugLineStrip*> lineStrips;

	std::vector<DebugLineSegment> lines; // Used when constructing line strips.

	Mesh* circleMesh;
	Mesh* rectangleMesh;
};

//------------------------------------------------------------------------------
