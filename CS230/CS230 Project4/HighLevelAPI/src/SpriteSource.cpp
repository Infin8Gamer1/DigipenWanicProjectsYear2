//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"
#include <Vector2D.h>
#include <Texture.h>
#include <Parser.h>
#include <ResourceManager.h>
#include <Texture.h>

SpriteSource::SpriteSource(unsigned numColsInput, unsigned numRowsInput, unsigned frameCount, unsigned frameStart, Texture * textureInput) : Serializable()
{
	numRows = numRowsInput;
	numCols = numColsInput;
	texture = textureInput;
	name = textureInput->GetName() + "_" + std::to_string(frameStart) + "_" + std::to_string(frameCount);
}

SpriteSource::~SpriteSource()
{
	delete texture;
	texture = nullptr;
}

void SpriteSource::Deserialize(Parser & parser)
{
	std::string textureName;
	parser.ReadVariable("textureName", textureName);
	parser.ReadVariable("textureRows", numRows);
	parser.ReadVariable("textureColumns", numCols);
	parser.ReadVariable("frameCount", frameCount);
	parser.ReadVariable("frameStart", frameStart);

	if (textureName != "null" && textureName != "none") {
		texture = Texture::CreateTextureFromFile(textureName);
	}

	ResourceManager::GetInstance().AddSpriteSource(this);
}

void SpriteSource::Serialize(Parser & parser) const
{
	parser.WriteVariable("textureName", GetTexture()->GetName());
	parser.WriteVariable("textureRows", numRows);
	parser.WriteVariable("textureColumns", numCols);
	parser.WriteVariable("frameCount", frameCount);
	parser.WriteVariable("frameStart", frameStart);
}

Texture * SpriteSource::GetTexture() const
{
	return texture;
}

void SpriteSource::SetTexture(Texture * texture)
{
	this->texture = texture;
}

unsigned SpriteSource::GetFrameCountTexture() const
{
	return numRows * numCols;
}

unsigned SpriteSource::GetFrameCount() const
{
	return frameCount;
}

unsigned SpriteSource::GetFrameStart() const
{
	return frameStart;
}

std::string SpriteSource::GetName() const
{
	return name;
}

void SpriteSource::SetName(std::string Name) const
{
	name;
}

const Vector2D SpriteSource::GetUV(unsigned int frameIndex) const
{
	float k_X = 1.0f / static_cast<float>(numCols);
	float k_Y = 1.0f / static_cast<float>(numRows);

	float xOffset = k_X * (frameIndex % numCols);
	float yOffset = k_Y * (frameIndex / numCols);

	return Vector2D(xOffset, yOffset);
}

const std::string & SpriteSource::GetTextureName() const
{
	return texture->GetName();
}

const Vector2D SpriteSource::GetTextureDimensions() const
{
	return Vector2D(numCols, numRows);
}
