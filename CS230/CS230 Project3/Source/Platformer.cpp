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

Levels::Platformer::Platformer() : Level("Platformer")
{
	//monkey
	meshMonkey = nullptr;
	textureMonkey = nullptr;
	spriteSourceMonkey = nullptr;

	columnsMonkey = 3;
	rowsMonkey = 5;

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
	textureCollectable = Texture::CreateTextureFromFile("Circle.png");
	spriteSourceCollectable = new SpriteSource(1, 1, textureCollectable);
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

	GameObject* Monkey = Archetypes::CreatePlatformerMonkey(meshMonkey, spriteSourceMonkey);
	static_cast<Animation*>(Monkey->GetComponent("Animation"))->Play(0, 8, 0.4f, false);
	GetSpace()->GetObjectManager().AddObject(*Monkey);

	GameObject* Collectable1 = Archetypes::CreateCollectable(meshCollectable, spriteSourceCollectable, Vector2D(-725, -25));
	GetSpace()->GetObjectManager().AddObject(*Collectable1);
}

void Levels::Platformer::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
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
}
