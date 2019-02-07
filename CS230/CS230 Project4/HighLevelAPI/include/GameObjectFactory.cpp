#include "stdafx.h"
#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject * GameObjectFactory::CreateObject(const std::string & name, Mesh * mesh, SpriteSource * spriteSource)
{
	return nullptr;
}

Component * GameObjectFactory::CreateComponent(const std::string & name)
{
	return nullptr;
}

void GameObjectFactory::SaveObjectToFile(GameObject * object)
{
}

GameObjectFactory & GameObjectFactory::GetInstance()
{
	// TODO: insert return statement here
}


