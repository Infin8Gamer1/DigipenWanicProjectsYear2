//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
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
#include "Transform.h"

#include <Vector2D.h>
#include <Matrix2D.h>
#include <Graphics.h>

#include "Parser.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a new transform object.
// Params:
//	 x = Initial world position on the x-axis.
//	 y = Initial world position on the y-axis.
Transform::Transform(float x, float y)
	: Component("Transform"), translation(x, y), scale(1.0f,1.0f),
	rotation(0.0f), isDirty(true)
{
}

// Transform constructor.
// Params:
//	 translation = World position of the object.
//   scale		 = Width and height of the object.
//   rotation	 = Rotation of the object about the z-axis.
Transform::Transform(Vector2D translation, Vector2D scale, float rotation)
	: Component("Transform"), translation(translation), scale(scale), 
	rotation(rotation), isDirty(true)
{
}

// Clone the transform, returning a dynamically allocated copy.
Component * Transform::Clone() const
{
	return new Transform(*this);
}

// Get the transform matrix, based upon translation, rotation and scale settings.
// Returns:
//   A reference to the component's matrix structure,
//		
const Matrix2D& Transform::GetMatrix() const
{
	CalculateMatrices();
	return matrix;
}

// Get the inverse of the transform matrix.
// Returns:
//	 A reference to the component's inverse matrix.
const Matrix2D & Transform::GetInverseMatrix() const
{
	CalculateMatrices();
	return inverseMatrix;
}

// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void Transform::SetTranslation(const Vector2D& translation_)
{
	if (!AlmostEqual(translation, translation_))
		isDirty = true;

	translation = translation_;
}

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 
//		A reference to the component's translation structure,
//		
const Vector2D& Transform::GetTranslation() const
{
	return translation;
}


// Set the rotation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 rotation = The rotation value (in radians).
void Transform::SetRotation(float rotation_)
{
	if (!AlmostEqual(rotation, rotation_))
		isDirty = true;

	rotation = rotation_;
}

// Get the rotation value of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//		The component's rotation value (in radians).
float Transform::GetRotation() const
{
	return rotation;
}

// Set the scale of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a scale vector.
void Transform::SetScale(const Vector2D& scale_)
{
	if (!AlmostEqual(scale, scale_))
		isDirty = true;

	scale = scale_;
}

// Get the scale of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 
//		A reference to the component's scale structure,
//		
const Vector2D& Transform::GetScale() const
{
	return scale;
}

// Calculates the transform matrix and its inverse using 
// translation, rotation, and scale.
void Transform::CalculateMatrices() const
{
	if (!isDirty)
		return;

	// TRANSFORM
	Matrix2D scaling = Matrix2D::ScalingMatrix(scale.x, scale.y);
	Matrix2D rot = Matrix2D::RotationMatrixRadians(rotation);
	Matrix2D trans = Matrix2D::TranslationMatrix(translation.x, translation.y);

	// Scaling is applied first, then rotation, then translation
	matrix = trans * rot * scaling;

	// INVERSE
	float inverseScaleX = (scale.x != 0.0f) ? (1.0f / scale.x) : 0.0f;
	float inverseScaleY = (scale.y != 0.0f) ? (1.0f / scale.y) : 0.0f;

	scaling = Matrix2D::ScalingMatrix(inverseScaleX, inverseScaleY);
	rot = Matrix2D::RotationMatrixRadians(-rotation);
	trans = Matrix2D::TranslationMatrix(-translation.x, -translation.y);

	// Reverse order for inverse
	inverseMatrix = scaling * rot * trans;

	isDirty = false;
}

// Save object data to file.
// Params:
//   parser = The parser object used to save the object's data.
void Transform::Serialize(Parser& parser) const
{
	parser.WriteVariable("translation", translation);
	parser.WriteVariable("rotation", rotation);
	parser.WriteVariable("scale", scale);
}

// Load object data from file
// Params:
//   parser = The parser object used to load the object's data.
void Transform::Deserialize(Parser& parser)
{
	parser.ReadVariable("translation", translation);
	parser.ReadVariable("rotation", rotation);
	parser.ReadVariable("scale", scale);
}
