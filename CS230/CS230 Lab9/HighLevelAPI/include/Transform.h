//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h"
#include "Matrix2D.h"
#include "Shapes2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// An example of the structure to be defined in Transform.h.
// You are free to change the contents of this structure as long as you do not
//   change the public method declarations declared in the header.
class Transform : public Component
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Transform constructor.
	// Params:
	//	 x = Initial world position on the x-axis.
	//	 y = Initial world position on the y-axis.
	Transform(float x, float y);

	// Transform constructor.
	// Params:
	//	 translation = World position of the object.
	//   scale		 = Width and height of the object.
	//   rotation	 = Rotation of the object about the z-axis.
	Transform(Vector2D translation = Vector2D(), Vector2D scale = Vector2D(1,1), float rotation = 0);

	// Clones the transform component, returning a dynamically allocated copy.
	Component* Clone() const;

	// Get the transform matrix, based upon translation, rotation and scale settings.
	// Returns:
	//	 A reference to the transform's matrix.
	const Matrix2D& GetMatrix() const;

	// Get the inverse of the transform matrix.
	// Returns:
	//	 A reference to the transform's inverse matrix.
	const Matrix2D& GetInverseMatrix() const;

	// Set the translation of a transform component.
	// Params:
	//	 translation = Reference to a translation vector.
	void SetTranslation(const Vector2D& translation);

	// Get the translation of a transform component.
	// Returns:
	//	 A reference to the component's translation structure.
	const Vector2D& GetTranslation() const;

	// Set the rotation of a transform component.
	// Params:
	//	 rotation = The rotation value (in radians).
	void SetRotation(float rotation);

	// Get the rotation value of a transform component.
	// Returns:
	//	 The component's rotation value (in radians).
	float GetRotation() const;

	// Set the scale of a transform component.
	// Params:
	//	 translation = Reference to a scale vector.
	void SetScale(const Vector2D& scale);

	// Get the scale of a transform component.
	// Returns:
	//	 A reference to the component's scale structure.
	const Vector2D& GetScale() const;

	// Returns a bounding rectangle using translation and (half) scale.
	const BoundingRectangle GetBounds() const;

	// Tests whether the object is visible on screen.
	bool IsOnScreen() const;

	// Save object data to file.
	// Params:
	//   parser = The parser object used to save the object's data.
	void Serialize(Parser& parser) const;

	// Load object data from file
	// Params:
	//   parser = The parser object used to load the object's data.
	void Deserialize(Parser& parser);

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Calculates the transform matrix and its inverse using translation, rotation, and scale.
	void CalculateMatrices() const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// The translation (or world position) of a game object.
	Vector2D	translation;

	// The rotation (or orientation) of a game object.
	float	rotation;

	// The scale (or size) of a game object.
	// This should be initialized to (1, 1).
	Vector2D	scale;

	// The transformation matrix resulting from concatenating translation, 
	// rotation, and scale matrices.
	mutable Matrix2D matrix;

	// The inverse of the transformation matrix. 
	mutable Matrix2D inverseMatrix;

	// True if the transformation matrix needs to be recalculated.
	// This should be initialized to true.
	mutable bool isDirty;
};
//------------------------------------------------------------------------------
