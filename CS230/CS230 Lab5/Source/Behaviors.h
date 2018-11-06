//------------------------------------------------------------------------------
//
// File Name:	Behaviors.h
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
// Forward References:
//------------------------------------------------------------------------------

class Transform;
class Physics;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

namespace Behaviors
{
	// Movement behavior for the triangle/ship.
	// Params:
	//	 transform = The transform component of the ship.
	//   physics = The physics component of the ship.
	void UpdateShip(Transform* transform, Physics* physics);
	
	// Movement behavior for the monkey.
	// Params:
	//	 transform = The transform component of the monkey.
	//   physics = The physics component of the monkey.
	void UpdateMonkey(Transform* transform, Physics* physics);
}
