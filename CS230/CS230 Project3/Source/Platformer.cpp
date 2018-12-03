#include "stdafx.h"
#include "Platformer.h"
#include "Space.h"
#include "MeshHelper.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Animation.h"
#include "Level1.h"
#include "Transform.h"
#include "Physics.h"
#include "Archetypes.h"
#include <Input.h>
#include <Mesh.h>
#include <gdiplus.h>
#include <Texture.h>
#include <Engine.h>
#include "Level3.h"
#include "Tilemap.h"
#include "MonkeyMovement.h"
#include "WinLevel.h"
#include "ColliderTilemap.h"

Levels::Platformer::Platformer() : Level("Platformer")
{
	//monkey
	meshMonkey = nullptr;
	textureMonkey = nullptr;
	spriteSourceMonkey = nullptr;

	columnsMonkey = 3;
	rowsMonkey = 5;

	MonkeyGO = nullptr;

	//map
	dataMap = nullptr;
	textureMap = nullptr;
	spriteSourceMap = nullptr;
	meshMap = nullptr;

	columnsMap = 4;
	rowsMap = 3;

	//collectables
	meshCollectable = nullptr;
	spriteSourceCollectable = nullptr;
	textureCollectable = nullptr;

	//hazards
	meshHazard = nullptr;
	spriteSourceHazard = nullptr;
	textureHazard = nullptr;

	//misc
	LevelCoinCount = 3;
}

void Levels::Platformer::Load()
{
	std::cout << "Platformer::Load" << std::endl;

	//monkey
	Vector2D textureSize = Vector2D(1.0f / columnsMonkey, 1.0f / rowsMonkey);
	meshMonkey = CreateQuadMesh(textureSize, Vector2D(1, 1));

	textureMonkey = Texture::CreateTextureFromFile("Monkey.png");

	spriteSourceMonkey = new SpriteSource(columnsMonkey, rowsMonkey, textureMonkey);

	//map
	Vector2D textureSizeMap = Vector2D(1.0f / columnsMap, 1.0f / rowsMap);
	meshMap = CreateQuadMesh(textureSizeMap, Vector2D(1, 1));

	textureMap = Texture::CreateTextureFromFile("Tilemap.png");

	spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);

	//collectable
	meshCollectable = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));
	textureCollectable = Texture::CreateTextureFromFile("Coin.png");
	spriteSourceCollectable = new SpriteSource(1, 1, textureCollectable);

	GameObject* Collectable = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, Vector2D(0, 0));
	GetSpace()->GetObjectManager().AddObject(*Collectable);

	//hazard
	meshHazard = CreateQuadMesh(Vector2D(1, 1), Vector2D(1, 1));
	textureHazard = Texture::CreateTextureFromFile("Hazard.png");
	spriteSourceHazard = new SpriteSource(1, 1, textureHazard);
}

void Levels::Platformer::Initialize()
{
	std::cout << "Platformer::Initialize" << std::endl;

	dataMap = Tilemap::CreateTilemapFromFile("Assets/Levels/PlatformerTilemap.txt");
	if (dataMap == nullptr)
	{
		std::cout << "Error Loading Tilemap!";
	}

	GameObject* Map = Archetypes::CreatePlatformerTilemapObject(meshMap, spriteSourceMap, dataMap);
	GetSpace()->GetObjectManager().AddObject(*Map);

	ColliderTilemap* ct = static_cast<ColliderTilemap*>(Map->GetComponent("Collider"));

	MonkeyGO = Archetypes::CreatePlatformerMonkey(meshMonkey, spriteSourceMonkey);
	static_cast<Animation*>(MonkeyGO->GetComponent("Animation"))->Play(0, 8, 0.05f, false);
	GetSpace()->GetObjectManager().AddObject(*MonkeyGO);

	GameObject* Collectable1 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, ct->ConvertTileMapCordsToWorldCords(Vector2D(2,5)));
	GetSpace()->GetObjectManager().AddObject(*Collectable1);

	GameObject* Collectable2 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, Vector2D(-310, 275));
	GetSpace()->GetObjectManager().AddObject(*Collectable2);

	GameObject* Collectable3 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, Vector2D(-210, -325));
	GetSpace()->GetObjectManager().AddObject(*Collectable3);

	GameObject* Hazard1 = Archetypes::CreateHazard(meshHazard, spriteSourceHazard, Vector2D(-210, -325));
	GetSpace()->GetObjectManager().AddObject(*Hazard1);
}

void Levels::Platformer::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	Behaviors::MonkeyMovement* MM = static_cast<Behaviors::MonkeyMovement*>(MonkeyGO->GetComponent("MonkeyMovement"));

	//if we have collected all of the coins then go to the win level
	if (MM->GetCoinsCollected() >= LevelCoinCount) {
		GetSpace()->SetLevel(new Levels::WinLevel());
	}
	else if (MM->GetHealth() <= 0) {
		GetSpace()->RestartLevel();
	}
}

void Levels::Platformer::Unload()
{
	std::cout << "Platformer::Unload" << std::endl;

	//Monkey
	delete spriteSourceMonkey;
	spriteSourceMonkey = nullptr;
	delete meshMonkey;
	meshMonkey = nullptr;
	delete textureMonkey;
	textureMonkey = nullptr;

	//Tilemap
	delete dataMap;
	dataMap = nullptr;
	delete textureMap;
	textureMap = nullptr;
	delete spriteSourceMap;
	spriteSourceMap = nullptr;
	delete meshMap;
	meshMap = nullptr;

	//Collectables
	delete meshCollectable;
	meshCollectable = nullptr;
	delete spriteSourceCollectable;
	spriteSourceCollectable = nullptr;
	delete textureCollectable;
	textureCollectable = nullptr;

	//Hazards
	delete meshHazard;
	meshHazard = nullptr;
	delete spriteSourceHazard;
	spriteSourceHazard = nullptr;
	delete textureHazard;
	textureHazard = nullptr;
}
