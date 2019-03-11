#include "stdafx.h"
#include "Asteroid.h"
#include <GameObject.h>
#include <Space.h>
#include "PlayerShip.h"
#include <Physics.h>
#include <Transform.h>
#include <Parser.h>
#include <Random.h>
#include <ColliderCircle.h>

void Behaviors::DamageHandlerAsteroid(int ammount, std::string type, GameObject & damageCauser, GameObject & damageTaker)
{
	UNREFERENCED_PARAMETER(damageCauser);

	damageTaker.setHealth(damageTaker.getHealth() - ammount);

	Transform* asteroidTransform = damageTaker.GetComponent<Transform>();
	ColliderCircle* asteroidCollider = damageTaker.GetComponent<ColliderCircle>();

	float sizeChangePerHit = damageTaker.GetComponent<Asteroid>()->sizeChangePerHit;

	asteroidTransform->SetScale(asteroidTransform->GetScale() * sizeChangePerHit);
	asteroidCollider->SetRadius(asteroidCollider->GetRadius() * sizeChangePerHit);

	if (damageTaker.getHealth() <= 0) {
		damageTaker.Destroy();
		damageTaker.GetSpace()->GetObjectManager().GetObjectByName("Ship")->GetComponent<Behaviors::PlayerShip>()->IncreaseScore(1);
	}
}

Behaviors::Asteroid::Asteroid(float _speedMin, float _speedMax, float _strafeSpeedMin, float _strafeSpeedMax, float _sizeChangePerHit) : Component("Asteroid")
{
	speedMin = _speedMin;
	speedMax = _speedMax;
	strafeSpeedMin = _strafeSpeedMin;
	strafeSpeedMax = _strafeSpeedMax;
	sizeChangePerHit = _sizeChangePerHit;
}

Component * Behaviors::Asteroid::Clone() const
{
	return new Asteroid(speedMin, speedMax, strafeSpeedMin, strafeSpeedMax, sizeChangePerHit);
}

void Behaviors::Asteroid::Initialize()
{
	GetOwner()->setDamageHandler(DamageHandlerAsteroid);
	GetOwner()->setHealth(3);

	transform = GetOwner()->GetComponent<Transform>();
}

void Behaviors::Asteroid::Deserialize(Parser & parser)
{
	parser.ReadVariable("minSpeed", speedMin);
	parser.ReadVariable("maxSpeed", speedMax);
	parser.ReadVariable("sizeChangePerHit", sizeChangePerHit);
}

void Behaviors::Asteroid::Serialize(Parser & parser) const
{
	parser.WriteVariable("minSpeed", speedMin);
	parser.WriteVariable("maxSpeed", speedMax);
	parser.WriteVariable("sizeChangePerHit", sizeChangePerHit);
}

void Behaviors::Asteroid::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	//check if the asteroid is still in the arena and if it isn't then destroy it with fire and death
	if (transform->GetTranslation().y < -450 || transform->GetTranslation().y > 600) {
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

float Behaviors::Asteroid::getRandStrafeSpeed()
{
	return RandomRange(strafeSpeedMin, strafeSpeedMax);
}
