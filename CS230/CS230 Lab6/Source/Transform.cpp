//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"

Transform::Transform(float x, float y) : Component("Transform")
{
	translation = Vector2D(x, y);
	scale = Vector2D(50,50);
	rotation = 0.0f;

	matrix = CS230::Matrix2D();

	isDirty = true;
}

Transform::Transform(Vector2D _translation, Vector2D _scale, float _rotation) : Component("Transform")
{
	translation = _translation;
	scale = _scale;
	rotation = _rotation;

	matrix = CS230::Matrix2D();

	isDirty = true;
}

Component * Transform::Clone() const
{
	return new Transform(translation, scale, rotation);
}

const CS230::Matrix2D & Transform::GetMatrix()
{
	if (isDirty){
		CS230::Matrix2D translationMatrix = CS230::Matrix2D().TranslationMatrix(translation.x, translation.y);
		CS230::Matrix2D rotationMatrix = CS230::Matrix2D().RotationMatrixRadians(rotation);
		CS230::Matrix2D scalingMatrix = CS230::Matrix2D().ScalingMatrix(scale.x, scale.y);

		matrix = translationMatrix * rotationMatrix * scalingMatrix;

		isDirty = false;
	}

	return matrix;
}

void Transform::SetTranslation(const Vector2D & _translation)
{
	translation = _translation;

	isDirty = true;
}

const Vector2D & Transform::GetTranslation() const
{
	return translation;
}

void Transform::SetRotation(float _rotation)
{
	rotation = _rotation;

	isDirty = true;
}

void Transform::LookAt(Vector2D _target)
{
	Vector2D dif = _target - translation;

	dif.Normalized();

	SetRotation(atan2(dif.y, dif.x));
}

float Transform::GetRotation() const
{
	return rotation;
}

void Transform::SetScale(const Vector2D & _scale)
{
	scale = _scale;

	isDirty = true;
}

const Vector2D & Transform::GetScale() const
{
	return scale;
}
