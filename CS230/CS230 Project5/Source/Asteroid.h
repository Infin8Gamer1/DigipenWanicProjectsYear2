//------------------------------------------------------------------------------
//
// File Name:	Asteroid.h
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

#include "Component.h" // base class

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Physics;
struct Event;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class Asteroid : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Asteroid constructor
		// Params:
		//   speedMin = Minimum of range for asteroid movement speed.
		//   speedMax = Maximum of range for asteroid movement speed.
		//   basePointsValue = Point value for largest asteroid.
		//   sizePointsModifier = Multiplicative scale applied to points for smaller asteroids.
		//   spawnScaleModifier = Percentage of original asteroid's scale to use for new asteroids.
		Asteroid(float speedMin = 50.0f, float speedMax = 100.0f);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		float getRandSpeed();

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// The damage handling function for Asteroids.
		static friend void DamageHandlerAsteroid(int ammount, std::string type, GameObject& damageCauser, GameObject& damageTaker);

		//------------------------------------------------------------------------------
		// Private Structures:
		//------------------------------------------------------------------------------

		enum Size
		{
			SizeSmall,
			SizeMedium,
			SizeLarge,
		};

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Properties (save to/load from file)
		float speedMin;
		float speedMax;

		// Other variables
		Size size;

		// Components
		Transform* transform;
	};
}

//------------------------------------------------------------------------------
