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
#include <Mesh.h>
#include <Vertex.h>
#include <Graphics.h>

Sprite::Sprite(Transform* _transform)
{
	transform = _transform;
	frameIndex = 0;
	spriteSource = nullptr;
	mesh = nullptr;
	color = Color();
}

void Sprite::Draw() const
{
	if (mesh == nullptr || transform == nullptr) {
		return;
	}

	if (spriteSource != nullptr) {

		Vector2D textureCords = Vector2D(0, 0);
		spriteSource->GetUV(frameIndex, textureCords);
		Graphics::GetInstance().SetTexture(spriteSource->GetTexture(), textureCords);
	} else {
		Graphics::GetInstance().SetTexture(nullptr);
	}

	//Graphics::GetInstance().SetTransform(transform->GetTranslation(), transform->GetScale(), transform->GetRotation());
	Graphics::GetInstance().SetTransform(reinterpret_cast<const Matrix2D&>(transform->GetMatrix()));

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

	std::cout << "Sprite::SetFrame(" << frameIndexInput << ")" << std::endl;

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
