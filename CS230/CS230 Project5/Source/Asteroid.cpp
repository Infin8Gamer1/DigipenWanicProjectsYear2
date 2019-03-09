#include "stdafx.h"
#include "Asteroid.h"
#include <GameObject.h>
#include <Space.h>
#include "PlayerShip.h"
#include <Physics.h>
#include <Random.h>
#include <Transform.h>

void Behaviors::DamageHandlerAsteroid(int ammount, std::string type, GameObject & damageCauser, GameObject & damageTaker)
{
	UNREFERENCED_PARAMETER(damageCauser);

	damageTaker.setHealth(damageTaker.getHealth() - ammount);

	if (damageTaker.getHealth() <= 0) {
		damageTaker.Destroy();
		damageTaker.GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent<Behaviors::PlayerShip>()->IncreaseScore(1);
	}
}

Behaviors::Asteroid::Asteroid(float _speedMin, float _speedMax) : Component("Asteroid")
{
	speedMin = _speedMin;
	speedMax = _speedMax;

	size = Size::SizeLarge;
}

Component * Behaviors::Asteroid::Clone() const
{
	return new Asteroid(speedMin, speedMax);
}

void Behaviors::Asteroid::Initialize()
{
	GetOwner()->setDamageHandler(DamageHandlerAsteroid);
	GetOwner()->setHealth(3);

	transform = GetOwner()->GetComponent<Transform>();
}

void Behaviors::Asteroid::Update(float dt)
{
	//check if the asteroid is still in the arena and if it isn't then destroy it with fire and death
	if (transform->GetTranslation().y < -450) {
		GetOwner()->Destroy();
	}
	else if (transform->GetTranslation().x > 750 || transform->GetTranslation().x < -750) {
		GetOwner()->Destroy();
	}
}

float Behaviors::Asteroid::getRandSpeed()
{
	return RandomRange(speedMin, speedMax);
}
