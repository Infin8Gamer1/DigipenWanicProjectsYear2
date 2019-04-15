//------------------------------------------------------------------------------
//
// File Name:	GameObject.h
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

#include "Serializable.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Component;
class Space;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class GameObject : public BetaObject, public Serializable
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a new game object.
	// Params:
	//	 name = The name of the game object being created.
	GameObject(const std::string& name);

	// Clone a game object from another game object.
	// Params:
	//	 other = A reference to the object being cloned.
	GameObject(const GameObject& other);

	// Free the memory associated with a game object.
	~GameObject();

	// Adds a component to the object.
	void AddComponent(Component* component);

	// Retrieves the component with the given type if it exists.
	template<typename ComponentType>
	ComponentType* GetComponent()
	{
		size_t numComponents = components.size();

		for (size_t i = 0; i < numComponents; ++i)
		{
			ComponentType* c = dynamic_cast<ComponentType*>(components[i]);
			// If the type name contains the name we're searching for, return it
			if (c != nullptr)
				return c;
		}

		return nullptr;
	}

	// Initialize this object's components and set it to active.
	void Initialize() override;

	// Whether the object has been marked for destruction.
	// Returns:
	//		True if the object will be destroyed, false otherwise.
	bool IsDestroyed() const;

	// Update any components attached to the game object.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Update(float dt) override;

	// Updates components using a fixed timestep (usually just physics)
	// Params:
	//	 dt = A fixed change in time, usually 1/60th of a second.
	void FixedUpdate(float dt) override;

	// Draw any visible components attached to the game object.
	void Draw() override;

	// Mark an object for destruction.
	void Destroy();

	// Tells whether an object will be updated.
	bool IsActive() const;

	// Sets whether an object will be updated.
	void SetActive(bool value);

	// Get the space that contains this object.
	Space* GetSpace() const;

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

	// Array of components
	std::vector<Component*> components;

	// Whether or not the object should be updated and drawn.
	bool active;

	// Whether the object has been marked for destruction.
	bool isDestroyed;
};

//------------------------------------------------------------------------------
