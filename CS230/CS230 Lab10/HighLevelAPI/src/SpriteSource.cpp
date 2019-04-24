//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"

#include "Texture.h"
#include "Vector2D.h" // SetX and SetY

//------------------------------------------------------------------------------

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
SpriteSource::SpriteSource(Texture* texture, int numCols, int numRows, int frameCount,
	int frameStart)
	: numCols(numCols), numRows(numRows), frameCount(frameCount), frameStart(frameStart), texture(texture)
{
}

// Returns a pointer to the texture, for the purposes of rendering a sprite.
Texture* SpriteSource::GetTexture() const
{
	return texture;
}

// Returns the maximum number of frames in the sprite source.
unsigned SpriteSource::GetFrameCount() const
{
	return frameCount;
}

// Returns the first valid index for this sprite source.
unsigned SpriteSource::GetFrameStart() const
{
	return frameStart;
}

// Returns the number of total frames in the source texture (rows * columns).
unsigned SpriteSource::GetTextureFrameCount() const
{
	return numRows * numCols;
}

// Stores the UV coordinates of the specified frame in the given vector.
// Params:
//	 frameIndex = A frame index within a sprite sheet.
//   textureCoords = Vector that will contain the UV coordinates.
const Vector2D SpriteSource::GetUV(unsigned frameIndex) const
{
	Vector2D textureCoords;

	float uSize = 1.0f / numCols;
	float vSize = 1.0f / numRows;
	
	unsigned column = frameIndex % numCols;
	unsigned row = frameIndex / numCols;

	textureCoords.x = uSize * column;
	textureCoords.y = vSize * row;

	return textureCoords;
}
