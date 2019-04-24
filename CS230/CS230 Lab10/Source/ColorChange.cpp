//------------------------------------------------------------------------------
//
// File Name:	ColorChange.cpp
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

#include "stdafx.h"		// Precompiled header
#include "ColorChange.h"	// Class file

// Systems
#include <Parser.h> // Read/WriteVariable

// Components
#include <GameObject.h>
#include <Sprite.h>
#include <Collider.h>
#include <Event.h>

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   normalColor = The color that the object reverts to when not colliding.
	//   collidedColor = The color that the object changes to when colliding.
	//   collidedColorTime = The amount of time the object will retain the collided color.
	ColorChange::ColorChange(const Color & normalColor, const Color & collidedColor)
		: Component("ColorChange"), normalColor(normalColor), collidedColor(collidedColor)
	{
	}

	// Return a new copy of the component.
	Component * ColorChange::Clone() const
	{
		return new ColorChange(*this);
	}

	// Initialize data for this object.
	void ColorChange::Initialize()
	{
		// Grab sprite
		sprite = GetOwner()->GetComponent<Sprite>();

		sprite->SetColor(normalColor);
	}

	void ColorChange::HandleEvent(const Event & event)
	{
		if (event.type == EventType::ET_Collision)
		{
			if (event.name == "CollisionEnded")
			{
				sprite->SetColor(normalColor);
			}

			if (event.name == "CollisionStarted" || event.name == "CollisionPersisted")
			{
				sprite->SetColor(collidedColor);
			}
		}
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void ColorChange::Serialize(Parser& parser) const
	{
		parser.WriteVariable("normalColor", normalColor);
		parser.WriteVariable("collidedColor", collidedColor);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void ColorChange::Deserialize(Parser& parser)
	{
		parser.ReadVariable("normalColor", normalColor);
		parser.ReadVariable("collidedColor", collidedColor);
	}
}
