#include "stdafx.h"
#include "TimedDeath.h"

Behaviors::TimedDeath::TimedDeath() : Component("TimedDeath")
{
	timeUntilDeath = 10.0f;
}

Behaviors::TimedDeath::TimedDeath(float _timeUntilDeath) : Component("TimedDeath")
{
	timeUntilDeath = _timeUntilDeath;
}

Behaviors::TimedDeath::~TimedDeath()
{
}

Component * Behaviors::TimedDeath::Clone() const
{
	return nullptr;
}

void Behaviors::TimedDeath::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}
