//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>
#include "Color.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef class Mesh Mesh;
typedef class SpriteSource SpriteSource;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class Sprite : public BetaObject
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new sprite object.
	Sprite();

	// Draw a sprite (Sprite can be textured or untextured).
	void Draw() const override;

	// Set a sprite's transparency (between 0.0f and 1.0f).
	// Params:
	//   alpha = New value for the sprite's 'alpha' value.
	void SetAlpha(float alpha);
	
	// Get the current value for a sprite's transparency.
	float GetAlpha() const;

	// Set the sprite's current frame.
	// (NOTE: You must validate the frame index against the sprite source's frame count.)
	// Params:
	//   frameIndex = New frame index for the sprite (0 .. frame count).
	void SetFrame(unsigned int frameIndex);

	// Returns the index of the current frame being displayed.
	unsigned GetFrame() const;

	// Set the sprite's mesh.
	// (NOTE: This mesh may be textured or untextured.)
	// (NOTE: This mesh may contain any number of triangles.)
	// Params:
	//   mesh = Pointer to a mesh created using the Alpha Engine.
	void SetMesh(Mesh* mesh);

	// Set a new SpriteSource for the specified sprite.
	// Params:
	//	 spriteSource = A new sprite source for the sprite.
	void SetSpriteSource(SpriteSource* spriteSource);

	// Set the blend color for the specified sprite.
	// Params:
	//	 color = A new color for the sprite.
	void SetColor(Color color);

	// Retrieves the blend color for the sprite.
	const Color& GetColor() const;

private:
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The sprite source used when drawing (simple colored mesh will have no sprite source).
	SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	Mesh* mesh;

	// Color used for blending/tint
	Color color;
};

//------------------------------------------------------------------------------
