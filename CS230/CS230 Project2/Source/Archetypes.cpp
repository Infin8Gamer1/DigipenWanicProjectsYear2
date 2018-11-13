#include "stdafx.h"
#include "Archetypes.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Animation.h"
#include "Physics.h"
#include "PlayerShip.h"
#include "TimedDeath.h"
#include "MonkeyMovement.h"

GameObject * Archetypes::CreateShip(Mesh * mesh)
{
	GameObject* ship = new GameObject("Ship");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(50, 50), 0.0f);
	ship->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	ship->AddComponent(sprite);
	//Physics
	Physics* physics = new Physics();
	ship->AddComponent(physics);
	//PlayerShip
	Behaviors::PlayerShip* ps = new Behaviors::PlayerShip();
	ship->AddComponent(ps);

	return ship;
}

GameObject * Archetypes::CreateBulletArchetype(Mesh * mesh)
{
	GameObject* bullet = new GameObject("Bullet");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(7, 7), 0.0f);
	bullet->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	bullet->AddComponent(sprite);
	//Physics
	Physics* physics = new Physics();
	bullet->AddComponent(physics);
	//TimedDeath
	Behaviors::TimedDeath* td = new Behaviors::TimedDeath();
	bullet->AddComponent(td);

	return bullet;
}

GameObject * Archetypes::CreateMonkey(Mesh * mesh, SpriteSource * spriteSource)
{
	GameObject* monkey = new GameObject("Monkey");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(200, 200), 0.0f);
	monkey->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	monkey->AddComponent(sprite);
	//Animation
	Animation* animation = new Animation();
	//animation->Play(0, 8, 0.4f, false);
	monkey->AddComponent(animation);
	//Physics
	Physics* physics = new Physics();
	physics->SetMass(1.0f);
	physics->SetGravity(Vector2D(0, -98.0f));
	monkey->AddComponent(physics);
	//Monkey Movement
	Behaviors::MonkeyMovement* mm = new Behaviors::MonkeyMovement();
	monkey->AddComponent(mm);

	return monkey;
}
