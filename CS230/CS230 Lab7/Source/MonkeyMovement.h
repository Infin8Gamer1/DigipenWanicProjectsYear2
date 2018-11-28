//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.h
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

#include "Vector2D.h" // Vector2D
#include "Collider.h" // MapCollision

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

typedef class Transform Transform;
typedef class Physics Physics;
typedef class Animation Animation;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class MonkeyMovement : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		MonkeyMovement();

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

		// Map collision handler for Monkey objects.
		// Params:
		//   object = The monkey object.
		//   collision = Which sides the monkey collided on.
		friend void MonkeyMapCollisionHandler(GameObject& object, MapCollision collision);

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		//moves the monkey using stuff and things
		void Move() const;

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Movement properties
		const float jumpForce = 5000.0f;
		const float strafeForce = 5.0f;
		Vector2D gravity;

		// Components
		Transform* transform;
		Physics* physics;
		Animation* animation;

		// Misc
		bool onGround;
		bool isFlying;
	};
}

//------------------------------------------------------------------------------
