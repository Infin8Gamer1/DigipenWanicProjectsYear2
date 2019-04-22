//------------------------------------------------------------------------------
//
// File Name:	Physics.cpp
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
#include "Physics.h"

#include "Vector2D.h"	// Vector2DScaleAdd
#include "Transform.h"	// TransformGetTranslation
#include "GameObject.h" // GetComponent
#include "Parser.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new physics component.
Physics::Physics()
	: Component("Physics"), angularVelocity(0.0), inverseMass(1.0f), transform(nullptr)
{
}

// Clone the physics component, returning a dynamically allocated copy.
Component * Physics::Clone() const
{
	return new Physics(*this);
}

// Initialize components.
void Physics::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
}

void Physics::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	// Calculate acceleration
	acceleration = inverseMass * forcesSum;
	// Reset sum of forces
	forcesSum = Vector2D();
}

// Update the state of a physics component.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void Physics::FixedUpdate(float dt)
{
	// Calculate new velocity from old velocity and acceleration
	velocity += acceleration * dt;
	// Save old translation
	oldTranslation = transform->GetTranslation();
	// Calculate new translation from old translation and velocity
	transform->SetTranslation(oldTranslation + velocity * dt);
	// Calculate new rotation from old rotation and angular velocity
	transform->SetRotation(transform->GetRotation() + angularVelocity * dt);
}

// Set the velocity of a physics component.
// Params:
//	 velocity = Pointer to a velocity vector.
void Physics::SetVelocity(const Vector2D& velocity_)
{
	velocity = velocity_;
}

// Get the velocity of a physics component.
// Returns: 
//		A pointer to the component's velocity structure,	
const Vector2D& Physics::GetVelocity() const
{
	return velocity;
}

// Set the angular velocity of a physics component.
// Params:
//	 velocity = New value for the angular velocity.
void Physics::SetAngularVelocity(float velocity_)
{
	angularVelocity = velocity_;
}

// Get the angular velocity of a physics component.
// Returns:
//	 A float representing the new angular velocity.
float Physics::GetAngularVelocity() const
{
	return angularVelocity;
}

// Set the mass of the physics component.
// Params:
//   mass = The new mass of the physics component.
void Physics::SetMass(float mass)
{
	inverseMass = 1.0f / mass;
}

// Add a force to the object.
// Params:
//	 force = A force vector with direction and magnitude.
void Physics::AddForce(const Vector2D& force)
{
	forcesSum += force;
}

// Get the acceleration of a physics component.
// Returns:
//		A pointer to the component's acceleration structure,
const Vector2D& Physics::GetAcceleration() const
{
	return acceleration;
}

// Get the old translation (position) of a physics component.
// Returns:
//		A pointer to the component's oldTranslation structure,
const Vector2D& Physics::GetOldTranslation() const
{
	return oldTranslation;
}

// Save object data to file.
// Params:
//   parser = The parser object used to save the object's data.
void Physics::Serialize(Parser& parser) const
{
	parser.WriteVariable("velocity", velocity);
	parser.WriteVariable("angularVelocity", angularVelocity);
	parser.WriteVariable("mass", 1.0f / inverseMass);
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void Physics::Deserialize(Parser& parser)
{
	parser.ReadVariable("velocity", velocity);
	parser.ReadVariable("angularVelocity", angularVelocity);
	float mass;
	parser.ReadVariable("mass", mass);
	inverseMass = 1.0f / mass;
}
