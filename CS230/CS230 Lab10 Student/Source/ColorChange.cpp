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
	ColorChange::ColorChange(const Color & normalColor, const Color & collidedColor, float collidedColorTime)
		: Component("ColorChange"), normalColor(normalColor), collidedColor(collidedColor), 
		collidedColorTime(collidedColorTime), collided(false), timer(0.0f)
	{
	}

	// Collision handler for ColorChange objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	void ColorChange::ColorChangeCollisionHandler(GameObject & object, GameObject & other)
	{
		UNREFERENCED_PARAMETER(other);

		// Get the color change component for the first object
		ColorChange* colorChange = object.GetComponent<ColorChange>();
		// Set collided variable to true
		colorChange->collided = true;
		colorChange->timer = colorChange->collidedColorTime;
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
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void ColorChange::Update(float dt)
	{
		if (collided)
		{
			// Set the color on the sprite to the collided color
			sprite->SetColor(collidedColor);
			collided = false;
		}
		else if(timer <= 0.0f)
		{
			// Set the color on the sprite to the non-collision color
			sprite->SetColor(normalColor);
		}

		// Decrease timer
		timer -= dt;
	}

	void ColorChange::HandleEvent(const Event & event)
	{
		if (event.type == EventType::ET_Collision)
		{
			GameObject* sender = static_cast<GameObject*>(GameObject::GetObjectByID(event.sender));
			GameObject* reviver = static_cast<GameObject*>(GameObject::GetObjectByID(event.receiver));

			ColorChangeCollisionHandler(*sender, *reviver);
		}
	}

	// Write object data to file
	// Params:
	//   parser = The parser that is writing this object to a file.
	void ColorChange::Serialize(Parser& parser) const
	{
		parser.WriteVariable("normalColor", normalColor);
		parser.WriteVariable("collidedColor", collidedColor);
		parser.WriteVariable("collidedColorTime", collidedColorTime);
	}

	// Read object data from a file
	// Params:
	//   parser = The parser that is reading this object's data from a file.
	void ColorChange::Deserialize(Parser& parser)
	{
		parser.ReadVariable("normalColor", normalColor);
		parser.ReadVariable("collidedColor", collidedColor);
		parser.ReadVariable("collidedColorTime", collidedColorTime);
	}
}
