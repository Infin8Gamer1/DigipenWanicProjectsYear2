//------------------------------------------------------------------------------
//
// File Name:	ScreenWrap.cpp
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
#include "ScreenWrap.h"

// Systems
#include <Graphics.h>	// GetScreenWorldDimensions

// Components
#include "GameObject.h" // GetComponent
#include "Transform.h"	// GetTranslation, SetTranslation
#include "Physics.h"	// GetVelocity

//------------------------------------------------------------------------------

namespace Behaviors
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	ScreenWrap::ScreenWrap()
		: Component("ScreenWrap")
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* ScreenWrap::Clone() const
	{
		return new ScreenWrap(*this);
	}

	// Initialize this component (happens at object creation).
	void ScreenWrap::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		physics = GetOwner()->GetComponent<Physics>();
	}

	// Fixed update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void ScreenWrap::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// Use velocity to determine which sides of screen to check
		const Vector2D& velocity = physics->GetVelocity();
		Vector2D scale = transform->GetScale() / 2.0f;
		Vector2D position = transform->GetTranslation();

		const BoundingRectangle& screenRect = Graphics::GetInstance().GetDefaultCamera().GetScreenWorldDimensions();

		if (velocity.x > 0.0f)
		{
			// Check right side, flip to left if too far past
			if (position.x > screenRect.right + scale.x)
				position.x = screenRect.left - scale.x;
		}
		else
		{
			// Check left side, flip to right if too far past
			if (position.x < screenRect.left - scale.x)
				position.x = screenRect.right + scale.x;
		}

		if (velocity.y > 0.0f)
		{
			// Check top side, flip to bottom if too far past
			if (position.y > screenRect.top + scale.y)
				position.y = screenRect.bottom - scale.y;
		}
		else
		{
			// Check bottom side, flip to top if too far past
			if (position.y < screenRect.bottom - scale.y)
				position.y = screenRect.top + scale.y;
		}

		transform->SetTranslation(position);
	}
}

//------------------------------------------------------------------------------
