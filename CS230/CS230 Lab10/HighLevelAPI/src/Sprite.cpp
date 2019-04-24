//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"

#include <Matrix2D.h>
#include <Mesh.h> // Draw
#include <Graphics.h> // SetTexture
#include "SpriteSource.h"

#include "Transform.h"	// GetMatrix
#include "GameObject.h"	// GetComponent
#include "Parser.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new sprite object.
Sprite::Sprite()
	: Component("Sprite"), frameIndex(0), spriteSource(nullptr), mesh(nullptr), transform(nullptr)
{
}

// Clone the sprite, returning a dynamically allocated copy.
Component* Sprite::Clone() const
{
	return new Sprite(*this);
}

// Initialize components.
void Sprite::Initialize()
{
	transform = GetOwner()->GetComponent<Transform>();
}

// Draw a sprite (Sprite can be textured or untextured).
void Sprite::Draw()
{
	// Call other draw function
	Draw(Vector2D(0.0f, 0.0f));
}

// Draw a sprite at an offset from the object's translation.
// Params:
//   offset = The offset that will be added to the translation when drawing.
void Sprite::Draw(const Vector2D& offset)
{
	// No mesh - get out!
	if (mesh == nullptr) return;

	if (spriteSource)
	{
		Texture* texture = spriteSource->GetTexture();
		Vector2D textureCoords = spriteSource->GetUV(frameIndex);
		texture->Use(textureCoords);
	}
	else Graphics::GetInstance().GetDefaultTexture().Use();

	// Set blend color
	Graphics::GetInstance().SetSpriteBlendColor(color);

	// Set transform using given translation
	Matrix2D offsetMatrix = Matrix2D::TranslationMatrix(offset.x, offset.y) 
		* transform->GetMatrix();
	Graphics::GetInstance().SetTransform(
		reinterpret_cast<const Matrix2D&>(offsetMatrix));

	// Draw!
	mesh->Draw();
}

// Set a sprite's transparency (between 0.0f and 1.0f).
// Params:
//   alpha = New value for the sprite's 'alpha' value.
void Sprite::SetAlpha(float alpha)
{
	color.a = std::max(alpha, 0.0f);
	color.a = std::min(alpha, 1.0f);
}

// Get the current value for a sprite's transparency.
float Sprite::GetAlpha() const
{
	return color.a;
}

// Set the sprite's current frame.
// (NOTE: You must validate the frame index against the sprite source's frame count.)
// Params:
//   frameIndex = New frame index for the sprite (0 .. frame count).
void Sprite::SetFrame(unsigned int frameIndex_)
{
	if (frameIndex < spriteSource->GetTextureFrameCount())
	{
		frameIndex = frameIndex_;
	}
}

// Returns the index of the current frame being displayed.
unsigned Sprite::GetFrame() const
{
	return frameIndex;
}

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//   mesh = Pointer to a mesh created using the Alpha Engine.
void Sprite::SetMesh(Mesh* mesh_)
{
	mesh = mesh_;
}

// Set a new SpriteSource for the specified sprite.
// Params:
//	 spriteSource = A new sprite source for the sprite.
void Sprite::SetSpriteSource(SpriteSource* spriteSource_)
{
	spriteSource = spriteSource_;
}

// Set the tint color for the specified sprite.
// Params:
//	 color = A new color for the sprite.
void Sprite::SetColor(Color color_)
{
	color = color_;
}

// Retrieves the blend color for the sprite.
const Color& Sprite::GetColor() const
{
	return color;
}

// Save object data to file.
// Params:
//   parser = The parser object used to save the object's data.
void Sprite::Serialize(Parser& parser) const
{
	parser.WriteVariable("color", color);
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void Sprite::Deserialize(Parser& parser)
{
	parser.ReadVariable("color", color);
}
