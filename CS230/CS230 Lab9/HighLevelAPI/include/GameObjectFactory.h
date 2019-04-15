//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		CS230
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

class GameObject;
class Component;
class Space;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class GameObjectFactory
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a single instance of the specified game object.
	// Loads the object from a text file (if it exists).
	// Params:
	//   name = The name of the object.
	//   space = The space the object will reside in.
	//   ignoreUnregisteredComponents = Whether to return the object even if it contains unregistered components.
	// Returns:
	//	 If the object file exists and can be loaded, then return a pointer to a new instance 
	//    of the specified game object type, else nullptr.
	GameObject* CreateObject(const std::string& name, Space* space = nullptr, bool ignoreUnregisteredComponents = false);

	// Create a single instance of the specified component.
	// Params:
	//   name = The name of the component.
	// Returns:
	//	 If the component exists, then return a pointer to a new instance 
	//    of the specified component, else nullptr.
	Component* CreateComponent(const std::string& name);

	// Saves an object to an archetype file so it can be loaded later.
	// Params:
	//   object = The object being saved to a file. Filename is based on object name.
	void SaveObjectToFile(const GameObject* object);

	// Register a component so it can be created on the fly.
	// Template parameters:
	//   ComponentType = The type of the component to be registered.
	template <class ComponentType>
	void RegisterComponent()
	{
		registeredComponents.push_back(new ComponentType());
	}

	// Returns an instance of the factory.
	static GameObjectFactory& GetInstance();

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Array containing all components used by objects.
	std::vector<Component*> registeredComponents;

	static const std::string objectFilePath;

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Constructor is private to prevent accidental instantiation
	GameObjectFactory();

	// Destructor is private to prevent accidental destruction
	~GameObjectFactory();
};

//------------------------------------------------------------------------------
