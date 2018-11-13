#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(const std::string & name) : BetaObject(name)
{
}

GameObject * Component::GetOwner() const
{
	return static_cast<GameObject*>(GetParent());
}
