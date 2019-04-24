//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Texture;
class Vector2D;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class SpriteSource
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new sprite source object.
	// Params:
	//	 texture = The texture that will be used with this sprite source.
	//	 numCols = The number of columns in the sprite sheet.
	//	 numRows = The number of rows in the sprite sheet.
	//   frameCount = The number of frames from the texture that will be used.
	//   frameStart = The first frame from the texture to use in the spriteSource.
	SpriteSource(Texture* texture, int numCols = 1, int numRows = 1, int frameCount = 1,
		int frameStart = 0);

	// Returns a pointer to the texture, for the purposes of rendering a sprite.
	Texture* GetTexture() const;

	// Returns the number of frames in the sprite source (for animation).
	unsigned GetFrameCount() const;
	
	// Returns the first valid index for this sprite source (for animation).
	unsigned GetFrameStart() const;

	// Returns the number of total frames in the source texture (rows * columns).
	unsigned GetTextureFrameCount() const;

	// Returns the UV coordinates of the specified frame in a sprite sheet.
	// Params:
	//	 frameIndex = A frame index within a sprite sheet.
	// Returns:
	//   A Vector2D containing the UV/texture coordinates.
	const Vector2D GetUV(unsigned frameIndex) const;

private:
	// The dimensions of the sprite sheet.
	unsigned numRows;
	unsigned numCols;

	// Number of frames in the sprite source.
	unsigned frameCount;
	
	// Starting frame for this sprite source.
	unsigned frameStart;
	
	// Pointer to a texture created using the Alpha Engine.
	Texture* texture;
};

//----------------------------------------------------------------------------
