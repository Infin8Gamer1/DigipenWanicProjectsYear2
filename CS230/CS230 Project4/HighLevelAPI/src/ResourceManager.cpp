//------------------------------------------------------------------------------
//
// File Name:	ResourceManager.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "SpriteSource.h"
#include "MeshHelper.h"
#include <Mesh.h>
#include <Texture.h>
#include <Parser.h>

static ResourceManager* Instance;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Shutdown();
}

Mesh * ResourceManager::GetMesh(const std::string & objectName, bool createIfNotFound, Vector2D textureSize, Vector2D textureExtents)
{
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		std::string currentName = Meshes[i]->GetName();

		if (currentName == objectName) {
			return Meshes[i];
		}
	}

	if (createIfNotFound) {
		Mesh* mesh = CreateQuadMesh(textureSize, textureExtents);

		mesh->SetName(objectName);

		AddMesh(mesh);

		return mesh;
	}
	
	return nullptr;
}

bool ResourceManager::MeshExists(const Mesh* mesh) {

	std::string meshName = mesh->GetName();

	for (size_t i = 0; i < Meshes.size(); i++)
	{
		std::string currentName = Meshes[i]->GetName();

		if (currentName == meshName) {
			return true;
		}
	}

	return false;
}

void ResourceManager::AddMesh(Mesh * mesh)
{
	if (!MeshExists(mesh)) {
		Meshes.push_back(mesh);
	}
	else {
		delete mesh;
	}
}

SpriteSource * ResourceManager::GetSpriteSource(const std::string & textureName, unsigned numCols, unsigned numRows, unsigned frameCount, unsigned frameStart, bool createIfNotFound)
{
	for (size_t i = 0; i < SpriteSources.size(); i++)
	{
		std::string currentName = SpriteSources[i]->GetName();

		std::vector<std::string> tokens = explodeString(currentName, '/');

		if (tokens.back() == textureName) {
			return SpriteSources[i];
		}
	}

	if (createIfNotFound) {
		Texture* texture = Texture::CreateTextureFromFile(textureName);
		SpriteSource* ss = new SpriteSource(numCols, numRows, frameCount, frameStart, texture);

		AddSpriteSource(ss);

		return ss;
	}

	return nullptr;
}

SpriteSource * ResourceManager::GetSpriteSource(const std::string & Name, bool createIfNotFound)
{
	for (size_t i = 0; i < SpriteSources.size(); i++)
	{
		std::string currentName = SpriteSources[i]->GetName();

		if (currentName == Name)
		{
			return SpriteSources[i];
		}
	}

	if (createIfNotFound) {
		Parser* parser = new Parser(Name + ".txt", std::fstream::in);

		SpriteSource* ss = new SpriteSource();

		ss->Deserialize(*parser);

		AddSpriteSource(ss);

		return ss;
	}

	return nullptr;
}

bool ResourceManager::SpriteSourceExists(const SpriteSource * ss)
{
	std::string ssName = ss->GetTexture()->GetName();

	for (size_t i = 0; i < SpriteSources.size(); i++)
	{
		std::string currentName = SpriteSources[i]->GetTexture()->GetName();

		std::vector<std::string> tokens = explodeString(currentName, '/');

		if (tokens.back() == ssName) {
			return true;
		}
	}

	return false;
}

void ResourceManager::AddSpriteSource(SpriteSource * ss)
{
	if (!SpriteSourceExists(ss)) {
		SpriteSources.push_back(ss);
	}
	else {
		delete ss;
	}
}

const Tilemap * ResourceManager::GetTilemap(const std::string & tilemapName, bool createIfNotFound)
{
	for (size_t i = 0; i < Tilemaps.size(); i++)
	{
		std::string currentName = Tilemaps[i]->GetName();

		if (currentName == tilemapName) {
			return Tilemaps[i];
		}
	}

	if (createIfNotFound) {
		Tilemap* map = Tilemap::CreateTilemapFromFile(tilemapName);

		if (map == nullptr)
		{
			std::cout << "Error Loading Tilemap!";

			delete map;
		} else {
			AddTilemap(map);

			return map;
		}
	}

	return nullptr;
}

bool ResourceManager::TilemapExists(Tilemap * map)
{
	std::string tilemapName = map->GetName();
	
	for (size_t i = 0; i < Tilemaps.size(); i++)
	{
		std::string currentName = Tilemaps[i]->GetName();

		if (currentName == tilemapName) {
			return true;
		}
	}

	return false;
}

void ResourceManager::AddTilemap(Tilemap * map)
{
	if (!TilemapExists(map)) {
		Tilemaps.push_back(map);
	}
	else {
		delete map;
	}
}

void ResourceManager::Shutdown()
{
	DeleteVector<Mesh>(Meshes);

	DeleteVector<SpriteSource>(SpriteSources);

	DeleteVector<Tilemap>(Tilemaps);
}

ResourceManager & ResourceManager::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new ResourceManager();
	}

	return *Instance;
}

std::vector<std::string> ResourceManager::explodeString(const std::string& str, const char& ch) {
	std::string next;
	std::vector<std::string> result;

	// For each character in the string
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the terminal character
		if (*it == ch) {
			// If we have some characters accumulated
			if (!next.empty()) {
				// Add them to the result vector
				result.push_back(next);
				next.clear();
			}
		}
		else {
			// Accumulate the next character into the sequence
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}
