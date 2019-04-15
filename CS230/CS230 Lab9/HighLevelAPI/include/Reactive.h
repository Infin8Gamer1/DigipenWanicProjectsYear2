//------------------------------------------------------------------------------
//
// File Name:	Reactive.h
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

#include "Component.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
class Vector2D;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef void(*MouseEventHandler)(GameObject& gameObject1);

class Reactive : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new Reactive component.
	Reactive();

	// Dynamically allocates a copy of a Reactive component.
	Component* Clone() const;

	// Check if the mouse is currently intersecting with this object.
	void Update(float dt);

	// Obtains the mouse's position in world coordinates.
	// Returns:
	//   The position of the mouse as a vector.
	Vector2D GetMouseWorldPosition() const;

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

	// Whether the mouse button is currently down.
	bool mouseIsDown;

	// Whether the mouse is currently over the object.
	bool mouseIsOver;
};

//------------------------------------------------------------------------------
