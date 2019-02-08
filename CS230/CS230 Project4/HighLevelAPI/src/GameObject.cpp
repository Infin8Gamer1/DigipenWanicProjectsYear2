//------------------------------------------------------------------------------
//
// File Name:	GameObject.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Space.h"
#include <Parser.h>
#include <GameObjectFactory.h>

GameObject::GameObject(const std::string & name) : BetaObject(name)
{
	numComponents = 0;
	isDestroyed = false;
}

GameObject::GameObject(const GameObject & other) : BetaObject(other.GetName())
{
	numComponents = 0;

	for (unsigned i = 0; i < other.numComponents; i++)
	{
		Component* newComp = other.components[i]->Clone();

		if (newComp != nullptr) {
			AddComponent(newComp);
		}
		
	}
	
	isDestroyed = false;
}

GameObject::~GameObject()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
}

void GameObject::Deserialize(Parser & parser)
{
	parser.ReadSkip(GetName());
	parser.ReadSkip('{');

	unsigned numComponents = 0;
	parser.ReadVar(numComponents);

	for (unsigned i = 0; i < numComponents; i++)
	{
		std::string componentName;
		parser.ReadValue(componentName);

		Component* component = GameObjectFactory::GetInstance().CreateComponent(componentName);

		if (component == nullptr) {
			throw ParseException(componentName, "Component could not be found! ERROR 404");
		}

		AddComponent(component);

		parser.ReadSkip('{');
		component->Deserialize(parser);
		parser.ReadSkip('}');
	}

	parser.ReadSkip('}');
}

void GameObject::Serialize(Parser & parser) const
{
	parser.WriteValue(GetName());

	parser.BeginScope();

	parser.WriteVar(numComponents);

	for (unsigned i = 0; i < numComponents; i++)
	{
		//write components name
		parser.WriteValue(std::string(typeid(*components[i]).name()).substr(6));

		parser.BeginScope();

		components[i]->Serialize(parser);

		parser.EndScope();
	}

	parser.EndScope();
}

void GameObject::Initialize()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Initialize();
	}
}

void GameObject::Update(float dt)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Update(dt);
	}
}

void GameObject::FixedUpdate(float dt)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->FixedUpdate(dt);
	}
}

void GameObject::Draw()
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		components[i]->Draw();
	}
}

void GameObject::AddComponent(Component * component)
{
	component->SetParent(this);
	components[numComponents] = component;
	numComponents++;
}

Component * GameObject::GetComponent(const std::string & _name)
{
	for (unsigned i = 0; i < numComponents; i++)
	{
		if (components[i]->GetName() == _name)
		{
			return components[i];
		}
	}
	//std::cout << "No component with the name " + _name + " was found!" << std::endl;
	return nullptr;
}

void GameObject::Destroy()
{
	isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

Space * GameObject::GetSpace() const
{
	return static_cast<Space*>(GetParent());
}
