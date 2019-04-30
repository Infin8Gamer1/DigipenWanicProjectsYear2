//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
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
#include "GameObject.h"

#include "Component.h"	// Clone
#include "Space.h"		// static_cast to Space*
#include "GameObjectFactory.h"	// CreateComponent
#include "Parser.h"		// WriteValue, ReadSkip, BeginScope, EndScope
#include <Event.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//Create a new game object.
// Params:
//	 name = The name of the game object being created.   
GameObject::GameObject(const std::string& name)
	: BetaObject(name), isDestroyed(false)
{
}

// Clone a game object from another game object.
// Params:
//	 other = A reference to the object being cloned.
GameObject::GameObject(const GameObject& other)
	: BetaObject(other.GetName()), isDestroyed(false)
{
	size_t numComponentsOther = other.components.size();
	for (size_t i = 0; i < numComponentsOther; ++i)
		AddComponent(other.components[i]->Clone());
}

// Free the memory associated with a game object.
GameObject::~GameObject()
{
	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
		delete components[i];
	components.clear();
}

void GameObject::HandleEvent(const Event & event)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->HandleEvent(event);
	}
}

// Initialize this object's components and set it to active.
void GameObject::Initialize()
{
	// Initialize the components
	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
		components[i]->Initialize();
}

// Update any components attached to the game object.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObject::Update(float dt)
{
	if (isDestroyed) return;

	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
		components[i]->Update(dt);
}

// Updates components using a fixed timestep (usually just physics)
// Params:
//	 dt = A fixed change in time, usually 1/60th of a second.
void GameObject::FixedUpdate(float dt)
{
	if (isDestroyed) return;
	
	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
		components[i]->FixedUpdate(dt);
}

// Draw any visible components attached to the game object.
void GameObject::Draw()
{
	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
		components[i]->Draw();
}

// Adds a component to the object.
void GameObject::AddComponent(Component * component)
{
	component->SetOwner(this);
	components.push_back(component);
}

// Retrieves the component with the given name if it exists.
// Params:
//   name = The name of the component to find.
Component * GameObject::GetComponent(const std::string & _name)
{
	size_t numComponents = components.size();
	for (size_t i = 0; i < numComponents; ++i)
	{
		if (_name == components[i]->GetName())
			return components[i];
	}

	return nullptr;
}

// Whether the object has been marked for destruction.
// Returns:
//		True if the object will be destroyed, false otherwise.
bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

// Mark an object for destruction.
void GameObject::Destroy()
{
	isDestroyed = true;

	GetSpace()->GetObjectManager().DispatchEvent(new Event(EventType::ET_ObjectDeleted, "Object " + GetName() + " Deleted", 0.0f, GetID()));
}

// Get the space that contains this object.
Space* GameObject::GetSpace() const
{
	return static_cast<Space*>(GetOwner());
}

// Save object data to file.
// Params:
//   parser = The parser object used to save the object's data.
void GameObject::Serialize(Parser& parser) const
{
	parser.WriteValue(GetName());
	parser.BeginScope();
	size_t numComponents = components.size();
	parser.WriteVariable("numComponents", numComponents);
	for (size_t i = 0; i < numComponents; ++i)
	{
		parser.WriteValue(std::string(typeid(*components[i]).name()).substr(6));
		parser.BeginScope();
		components[i]->Serialize(parser);
		parser.EndScope();
	}
	parser.EndScope();
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void GameObject::Deserialize(Parser& parser)
{
	parser.ReadSkip(GetName());
	parser.ReadSkip('{');
	unsigned numToAdd = 0;
	parser.ReadVariable("numComponents", numToAdd);
	std::string componentName;
	for (unsigned i = 0; i < numToAdd; ++i)
	{
		parser.ReadValue(componentName);
		Component* component = GameObjectFactory::GetInstance().CreateComponent(componentName);

		// Couldn't create component
		if (component == nullptr)
		{
			throw ParseException(GetName() + ".txt", "Unrecognized component name: " + componentName);
		}

		AddComponent(component);
		parser.ReadSkip('{');
		component->Deserialize(parser);
		parser.ReadSkip('}');
	}
	parser.ReadSkip('}');
}
