//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.h
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

#include "Sprite.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Tilemap;
class Area;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class SpriteTilemap : public Sprite
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new sprite for use with a tilemap.
	SpriteTilemap();

	// Clone the sprite, returning a dynamically allocated copy.
	Component* Clone() const override;

	// Get component dependencies.
	void Initialize() override;

	// Update area data.
	void Update(float dt) override;

	// Draw a sprite (Sprite can be textured or untextured).
	void Draw() override;

	// Sets the tilemap data that will be used by the sprite.
	// Params:
	//   map = A pointer to the tilemap resource.
	void SetTilemap(const Tilemap* map);

	// Loads object data from a file.
	// Params:
	//   parser = The parser for the file we want to read from.
	virtual void Deserialize(Parser& parser);

	// Saves object data to a file.
	// Params:
	//   parser = The parser for the file we want to write to.
	virtual void Serialize(Parser& parser) const;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The tilemap
	const Tilemap* map;

	// Area component
	Area* area;
};

//------------------------------------------------------------------------------
