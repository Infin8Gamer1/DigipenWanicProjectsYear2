//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderTilemap.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"
#include "ColliderRectangle.h"
#include <Shapes2D.h>
#include "Matrix2DStudent.h"
#include "Tilemap.h"

ColliderTilemap::ColliderTilemap() : Collider(ColliderType::ColliderTypeTilemap)
{
	map = nullptr;
}

Component * ColliderTilemap::Clone() const
{
	return new ColliderTilemap(*this);
}

void ColliderTilemap::Draw()
{
}

bool ColliderTilemap::IsCollidingWith(const Collider & other) const
{
	//check if it is a rectangle if it isn't then just return false and don't bother doing anything
	if (other.GetType() != ColliderType::ColliderTypeRectangle) {
		return false;
	}
	//get components
	Transform* otherTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));
	Physics* otherPhysics = static_cast<Physics*>(other.GetOwner()->GetComponent("Physics"));
	//create a bounding box for the other object
	BoundingRectangle otherRect = BoundingRectangle(otherTransform->GetTranslation(), static_cast<const ColliderRectangle&>(other).GetExtents());

	//check collision sides and store it in a MapCollision var
	bool bottom = IsSideColliding(otherRect, RectangleSide::SideBottom);
	bool left = IsSideColliding(otherRect, RectangleSide::SideLeft);
	bool right = IsSideColliding(otherRect, RectangleSide::SideRight);
	bool top = IsSideColliding(otherRect, RectangleSide::SideTop);
	MapCollision mapCollision = MapCollision(bottom, top, left, right);

	//resolve collisions
	if (mapCollision.bottom || mapCollision.top) {
		otherTransform->SetTranslation(Vector2D(otherTransform->GetTranslation().x, otherPhysics->GetOldTranslation().y));
		otherPhysics->SetVelocity(Vector2D(otherPhysics->GetVelocity().x, 0));
	}

	if (mapCollision.left) {
		otherTransform->SetTranslation(Vector2D(otherPhysics->GetOldTranslation().x, otherTransform->GetTranslation().y));
		if (otherPhysics->GetVelocity().x < 0) {
			otherPhysics->SetVelocity(Vector2D(0, otherPhysics->GetVelocity().y));
		}
	}
		
	if (mapCollision.right) {
		otherTransform->SetTranslation(Vector2D(otherPhysics->GetOldTranslation().x, otherTransform->GetTranslation().y));
		if (otherPhysics->GetVelocity().x > 0) {
			otherPhysics->SetVelocity(Vector2D(0, otherPhysics->GetVelocity().y));
		}
	}

	if (mapCollision.bottom || mapCollision.left || mapCollision.right || mapCollision.top) {
		//call collision handler for the other object
		other.GetMapCollisionHandler()(*other.GetOwner(), mapCollision);
		//we collided so return true
		return true;
	}

	//we didn't collide so return false
	return false;
}

void ColliderTilemap::SetTilemap(const Tilemap * _map)
{
	map = _map;
}

bool ColliderTilemap::IsSideColliding(const BoundingRectangle & rectangle, RectangleSide side) const
{
	bool isCollidingOnSide = false;
	Vector2D hotspots[3];

	float offset = 1.05f;

	if (side == RectangleSide::SideBottom) {
		//create 3 hotspots Left, Middle, Right
		hotspots[0] = Vector2D((rectangle.center.x + rectangle.extents.x / offset), rectangle.bottom);
		hotspots[1] = Vector2D(rectangle.center.x, rectangle.bottom);
		hotspots[2] = Vector2D((rectangle.center.x - rectangle.extents.x / offset), rectangle.bottom);
	} else if (side == RectangleSide::SideTop) {
		//create 3 hotspots Left, Middle, Right
		hotspots[0] = Vector2D((rectangle.center.x + rectangle.extents.x / offset), rectangle.top);
		hotspots[1] = Vector2D(rectangle.center.x, rectangle.top);
		hotspots[2] = Vector2D((rectangle.center.x - rectangle.extents.x / offset), rectangle.top);
	} else if (side == RectangleSide::SideLeft) {
		//create 3 hotspots Top, Middle, Bottom
		hotspots[0] = Vector2D(rectangle.left, (rectangle.center.y + rectangle.extents.y / offset));
		hotspots[1] = Vector2D(rectangle.left, rectangle.center.y);
		hotspots[2] = Vector2D(rectangle.left, (rectangle.center.y - rectangle.extents.y / offset));
	} else if (side == RectangleSide::SideRight) {
		//create 3 hotspots Top, Middle, Bottom
		hotspots[0] = Vector2D(rectangle.right, (rectangle.center.y + rectangle.extents.y / offset));
		hotspots[1] = Vector2D(rectangle.right, rectangle.center.y);
		hotspots[2] = Vector2D(rectangle.right, (rectangle.center.y - rectangle.extents.y / offset));
	}

	//for each hotspot check if it is colliding
	for (int i = 0; i < 3; i++)
	{
		//if we are colliding at the point then set isCollidingOnSide to true
		if (IsCollidingAtPosition(hotspots[i].x, hotspots[i].y)) {
			isCollidingOnSide = true;
		}
	}

	return isCollidingOnSide;
}

bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const
{
	//create a point in the normalized gridsystem that is the Tilemap
	Vector2D point = Vector2D(x , y);
	point = transform->GetInverseMatrix() * point;

	int x2 = static_cast<int>(point.x + 0.5f);
	int y2 = static_cast<int>(-point.y + 0.5f);

	int cellValue = map->GetCellValue(x2, y2);

	return (cellValue > 0);
}
