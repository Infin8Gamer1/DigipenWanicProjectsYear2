//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "GameObject.h"
#include <Mesh.h>
#include <Vertex.h>
#include <Graphics.h>
#include <Parser.h>
#include <ResourceManager.h>

Sprite::Sprite() : Component("Sprite")
{
	transform = nullptr;
	frameIndex = 0;
	spriteSource = nullptr;
	mesh = nullptr;
	color = Color();
}

Component * Sprite::Clone() const
{
	return new Sprite(*this);
}

void Sprite::Deserialize(Parser & parser)
{
	//get frame index
	parser.ReadVariable("frameIndex", frameIndex);
	//get color
	parser.ReadVariable("color", color);
	//get spritesource
	std::string textureName;
	parser.ReadVariable("textureName", textureName);
	int rows;
	parser.ReadVariable("textureRows", rows);
	int columns;
	parser.ReadVariable("textureColumns", columns);

	if (textureName != "null" && textureName != "none") {
		SetSpriteSource(ResourceManager::GetInstance().GetSpriteSource(textureName, columns, rows));
	}
	//get mesh
	SetMesh(ResourceManager::GetInstance().GetMesh(GetOwner()->GetName() + "_AutoMesh", true, Vector2D(1.0f / columns, 1.0f / rows)));
}

void Sprite::Serialize(Parser & parser) const
{
	//set frame index
	parser.WriteVariable("frameIndex", frameIndex);
	//set color
	parser.WriteVariable("color", color);
	//set texture
	if (spriteSource != nullptr) {
		parser.WriteVariable("textureName", spriteSource->GetTexture()->GetName());
		parser.WriteVariable("textureRows", spriteSource->numRows);
		parser.WriteVariable("textureColumns", spriteSource->numCols);
	} else {
		parser.WriteVariable("textureName", "null");
		parser.WriteVariable("textureRows", 1);
		parser.WriteVariable("textureColumns", 1);
	}
}

void Sprite::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
}

void Sprite::Draw()
{
	Draw(Vector2D(0, 0));
}

void Sprite::Draw(const Vector2D& offset)
{
	if (mesh == nullptr || transform == nullptr) {
		return;
	}

	if (spriteSource != nullptr) {

		Vector2D textureCords = Vector2D(0, 0);
		spriteSource->GetUV(frameIndex, textureCords);
		Graphics::GetInstance().SetTexture(spriteSource->GetTexture(), textureCords);
	}
	else {
		Graphics::GetInstance().SetTexture(nullptr);
	}

	Graphics::GetInstance().SetSpriteBlendColor(color);

	Matrix2D matrix = reinterpret_cast<const Matrix2D&>(transform->GetMatrix());
	Matrix2D offsetMatrix = Matrix2D().TranslationMatrix(offset.x, offset.y);
	Graphics::GetInstance().SetTransform(offsetMatrix * matrix);

	mesh->Draw();
}

void Sprite::SetAlpha(float alpha)
{
	color.a = alpha;
}

float Sprite::GetAlpha() const
{
	return color.a;
}

void Sprite::SetFrame(unsigned int frameIndexInput)
{
	if (spriteSource == nullptr) {
		return;
	}

	//std::cout << "Sprite::SetFrame(" << frameIndexInput << ")" << std::endl;

	if (frameIndexInput < spriteSource->GetFrameCount()) {
		frameIndex = frameIndexInput;
	}
}

unsigned Sprite::GetFrame() const
{
	return frameIndex;
}

void Sprite::SetMesh(Mesh * meshInput)
{
	mesh = meshInput;
}

void Sprite::SetSpriteSource(SpriteSource * spriteSourceInput)
{
	spriteSource = spriteSourceInput;
}

void Sprite::SetColor(Color colorInput)
{
	color = colorInput;
}

const Color & Sprite::GetColor() const
{
	return color;
}
