//------------------------------------------------------------------------------
//
// File Name:	BulletMovement.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Vector2D.h" // Vector2D

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

typedef class Transform Transform;
typedef class Physics Physics;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class Bullet : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Default constructor
		Bullet();

		// Non-default constructor
		// Params:
		//   timeUntilDeath = Amount of time until the object self-destructs.
		Bullet(Vector2D Direction, float Speed, int Damage);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Write object data to file
		// Params:
		//   parser = The parser that is writing this object to a file.
		void Serialize(Parser& parser) const override;

		// Read object data from a file
		// Params:
		//   parser = The parser that is reading this object's data from a file.
		void Deserialize(Parser& parser) override;

		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		void SetSpeed(float Speed);

		void SetDirection(Vector2D Direction);

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Amount of time until the object self-destructs.
		//float timeUntilDeath;
		Vector2D forceDirection;
		float speed;
		int damage;

		// The collision handling function for Asteroids.
		// Params:
		//	 asteroid = The asteroid.
		//   otherObject = The other object.
		static friend void CollisionHandlerBullet(GameObject& bullet, GameObject& other);
	};
}

//------------------------------------------------------------------------------
