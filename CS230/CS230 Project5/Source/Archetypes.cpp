//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

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
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"
#include <Graphics.h>
#include <GameObjectFactory.h>

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

	//GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerShip>();
	GameObjectFactory::GetInstance().SaveObjectToFile(ship);

	return ship;
}

GameObject * Archetypes::CreateMonkey(Mesh * mesh, SpriteSource * spriteSource)
{
	GameObject* monkey = new GameObject("Monkey");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(100, 100), 0.0f);
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
	//Box Collider
	ColliderRectangle* collider = new ColliderRectangle(Vector2D(abs(transform->GetScale().x / 2), abs(transform->GetScale().y / 2)));
	monkey->AddComponent(collider);
	//Monkey Movement
	Behaviors::MonkeyMovement* mm = new Behaviors::MonkeyMovement();
	monkey->AddComponent(mm);

	GameObjectFactory::GetInstance().SaveObjectToFile(monkey);

	return monkey;
}

GameObject * Archetypes::CreateCircle(Mesh * mesh, SpriteSource * spriteSource)
{
	GameObject* circle = new GameObject("Circle");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(100, 100), 0.0f);
	circle->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	circle->AddComponent(sprite);
	//Physics
	Physics* physics = new Physics();
	physics->SetMass(1.0f);
	//physics->SetGravity(Vector2D(0, -98.0f));
	circle->AddComponent(physics);
	//ColliderPoint
	ColliderCircle* collider = new ColliderCircle(50.0f);
	circle->AddComponent(collider);
	//ColorChange
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(1, 1, 0), Color(1, 0, 0));
	circle->AddComponent(colorChange);
	//Screen Wrap
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
	circle->AddComponent(screenWrap);

	GameObjectFactory::GetInstance().SaveObjectToFile(circle);

	return circle;
}

GameObject * Archetypes::CreatePoint(Mesh * mesh, SpriteSource * spriteSource)
{
	GameObject* point = new GameObject("Point");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(20, 20), 0.0f);
	point->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	point->AddComponent(sprite);
	//Physics
	Physics* physics = new Physics();
	physics->SetMass(1.0f);
	//physics->SetGravity(Vector2D(0, -98.0f));
	point->AddComponent(physics);
	//ColliderPoint
	ColliderPoint* collider = new ColliderPoint();
	point->AddComponent(collider);
	//ColorChange
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(0,0,1), Color(1,0,0));
	point->AddComponent(colorChange);
	//Screen Wrap
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
	point->AddComponent(screenWrap);

	GameObjectFactory::GetInstance().SaveObjectToFile(point);

	return point;
}

GameObject * Archetypes::CreateRectangle(Mesh * mesh)
{
	GameObject* circle = new GameObject("Rectangle");
	//transform
	Transform* transform = new Transform(Vector2D(0, 0), Vector2D(250, 100), 0.0f);
	circle->AddComponent(transform);
	//Sprite
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	circle->AddComponent(sprite);
	//Physics
	Physics* physics = new Physics();
	physics->SetMass(1.0f);
	//physics->SetGravity(Vector2D(0, -98.0f));
	circle->AddComponent(physics);
	//ColliderPoint
	ColliderRectangle* collider = new ColliderRectangle(Vector2D(abs(transform->GetScale().x / 2), abs(transform->GetScale().y / 2)));
	circle->AddComponent(collider);
	//ColorChange
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Color(0, 1, 0), Color(1, 0, 0));
	circle->AddComponent(colorChange);
	//Screen Wrap
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();
	circle->AddComponent(screenWrap);

	GameObjectFactory::GetInstance().SaveObjectToFile(circle);

	return circle;
}

GameObject * Archetypes::CreateTilemapObject(Mesh * mesh, SpriteSource * spriteSource, Tilemap * map)
{
	GameObject* tileMap = new GameObject("tileMap");
	//transform
	Transform* transform = new Transform(Vector2D(-350, 250), Vector2D(100, 100), 0.0f);
	tileMap->AddComponent(transform);
	//Sprite
	SpriteTilemap* sprite = new SpriteTilemap();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	sprite->SetTilemap(map);
	tileMap->AddComponent(sprite);
	//Collider Tilemap
	ColliderTilemap* colliderTilemap = new ColliderTilemap();
	colliderTilemap->SetTilemap(map);
	tileMap->AddComponent(colliderTilemap);

	GameObjectFactory::GetInstance().SaveObjectToFile(tileMap);

	return tileMap;
}
