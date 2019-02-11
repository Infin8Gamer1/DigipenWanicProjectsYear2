#include "stdafx.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "SpriteSource.h"
#include "MeshHelper.h"
#include <Mesh.h>
#include <Texture.h>

static ResourceManager* Instance;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Shutdown();
}

Mesh * ResourceManager::GetMesh(const std::string & objectName, bool createIfNotFound, Vector2D textureSize)
{
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		std::string currentName = Meshes[i]->GetName();

		if (currentName == objectName) {
			return Meshes[i];
		}
	}

	if (createIfNotFound) {
		Mesh* mesh = CreateQuadMesh(textureSize, Vector2D(1, 1));

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

SpriteSource * ResourceManager::GetSpriteSource(const std::string & textureName, int numCols, int numRows, bool createIfNotFound)
{
	for (size_t i = 0; i < SpriteSources.size(); i++)
	{
		std::string currentName = SpriteSources[i]->GetTexture()->GetName();

		std::vector<std::string> tokens = explodeString(currentName, '/');

		if (tokens.back() == textureName) {
			return SpriteSources[i];
		}
	}

	if (createIfNotFound) {
		Texture* texture = Texture::CreateTextureFromFile(textureName);
		SpriteSource* ss = new SpriteSource(numCols, numRows, texture);

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

Tilemap * ResourceManager::GetTilemap(const std::string & tilemapName, bool createIfNotFound, std::string FilePath)
{
	return nullptr;
}

bool ResourceManager::TilemapExists(const Tilemap * map)
{
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
