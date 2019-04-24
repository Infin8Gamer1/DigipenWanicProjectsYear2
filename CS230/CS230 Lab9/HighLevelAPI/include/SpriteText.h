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

#include "Sprite.h"
#include "Color.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Area;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class SpriteText : public Sprite
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new sprite object.
	// Params:
	//   text = The text to display.
	//   wrap = Whether to wrap text onto multiple lines
	//   rowLength = Characters to print before wrapping.
	SpriteText(const std::string& text = "", bool wrap = false,
		unsigned rowLength = 10);

	// Returns a dynamically allocated copy of the component.
	// Must be implemented so correct component is copied during copy.
	Component* Clone() const;

	// Get component dependencies.
	void Initialize() override;

	// Update function
	void Update(float dt) override;

	// Draw sprite text.
	void Draw() override;

	// Sets the text that will be displayed by the sprite.
	void SetText(const std::string& text);

	// Gets the text being displayed by the sprite.
	const std::string& GetText() const;

	// Save object data to file.
	// Params:
	//   parser = The parser object used to save the object's data.
	void Serialize(Parser& parser) const;

	// Load object data from file
	// Params:
	//   parser = The parser object used to load the object's data.
	void Deserialize(Parser& parser);

private:
	// The text that will be displayed.
	std::string text;

	// Wrap text?
	bool wrap;

	// Number of characters per row (for wrapping)
	unsigned rowLength;

	// Number of rows
	unsigned numRows;

	// Number of columns in the longest row
	unsigned maxColumns;

	// Area component
	Area* area;
};

//------------------------------------------------------------------------------
