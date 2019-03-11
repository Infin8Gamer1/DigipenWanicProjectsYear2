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
		Asteroid(float speedMin = 50.0f, float speedMax = 100.0f, float strafeSpeedMin = -60.0f, float strafeSpeedMax = 60.0f, float sizeChangePerHit = 0.7);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Loads object data from a file.
		void Deserialize(Parser& parser) override;

		// Saves object data to a file.
		void Serialize(Parser& parser) const override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		float getRandSpeed();

		float getRandStrafeSpeed();

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// The damage handling function for Asteroids.
		static friend void DamageHandlerAsteroid(int ammount, std::string type, GameObject& damageCauser, GameObject& damageTaker);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Properties (save to/load from file)
		float speedMin;
		float speedMax;
		float strafeSpeedMin;
		float strafeSpeedMax;
		float sizeChangePerHit;

		// Components
		Transform* transform;
	};
}

//------------------------------------------------------------------------------
