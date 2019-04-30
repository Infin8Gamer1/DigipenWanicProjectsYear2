//------------------------------------------------------------------------------
//
// File Name:	Quadtree.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Quadtree.h"
#include <Shapes2D.h>
#include <Graphics.h>
#include <DebugDraw.h>
#include "Intersection2D.h"
#include "GameObject.h"
#include "Transform.h"

enum Quadrants : short
{
	OUT_OF_BOUNDS = -2,
	PARTIAL_FIT = -1,
	TOP_RIGHT,
	TOP_LEFT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT,
	NUM_CHILDREN
};

Quadtree::Quadtree(const BoundingRectangle & bounds, int maxObjects, int maxTreeDepth, int level) : bounds(bounds), level(level),
	maxObjects(maxObjects), maxTreeDepth(maxTreeDepth)
{
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
}

Quadtree::~Quadtree()
{
	Clear();
}

void Quadtree::Draw() const
{
	if (IsLeafNode())
	{
		Camera& camera = Graphics::GetInstance().GetDefaultCamera();
		DebugDraw::GetInstance().AddRectangle(bounds.center, bounds.extents, camera, Colors::Violet);
	}
	else {
		for each (Quadtree* node in nodes)
		{
			node->Draw();
		}
	}
	
}

void Quadtree::AddObject(GameObject * object)
{
	// 1. First, use the GetIndex function to find the index of the object
	Quadrants index = GetIndex(object->GetComponent<Transform>()->GetBounds());

	// 2. If the object is not within node bounds (i.e., index is OUT_OF_BOUNDS)
	// Return!
	if (index == OUT_OF_BOUNDS)
	{
		return;
	}

	// 3. If we are at a leaf node (none of children have been allocated yet)
	if (IsLeafNode())
	{
		// If we are not at the tree's max depth and there are too many objects
		if (level < maxTreeDepth && objects.size() >= maxObjects)
		{
			// Split this node by calling the Split function
			Split();
			// Then try adding the object again (After splitting, there will be a different outcome.)
			AddObject(object);

			return;
		}

		// Else, number of objects is okay or we are at max depth, so push object onto list.
		objects.push_back(object);
	}
	// 4. Else, we are not at a leaf node
	else {
		// If object has total fit, add to the specific node that matches its index.
		if (index != PARTIAL_FIT)
		{
			// Call AddObject on the specific node that matches its index
			//nodes[index]->AddObject(object);
			switch (index)
			{
			case TOP_RIGHT:
				nodes[1]->AddObject(object);
				break;
			case TOP_LEFT:
				nodes[0]->AddObject(object);
				break;
			case BOTTOM_RIGHT:
				nodes[3]->AddObject(object);
				break;
			case BOTTOM_LEFT:
				nodes[2]->AddObject(object);
				break;
			default:
				break;
			}
		}
		// Else, object has partial fit, so for each subnode,
		else {
			for (size_t i = 0; i < 4; i++)
			{
				// Call AddObject on the subnode
				nodes[i]->AddObject(object);
			}
		}
	}

}

void Quadtree::RetrieveNearbyObjects(GameObject * object, std::vector<GameObject*>& results)
{
	// 1. First, as always, get the index of the object.
	Quadrants index = GetIndex(object->GetComponent<Transform>()->GetBounds());

	// 2. If the object is not within bounds,
	// LEAVE THIS PLACE YOU FOUL DEMON! (i.e. return)
	if (index == OUT_OF_BOUNDS)
	{
		return;
	}

	// 3. If we are at a leaf node
	if (IsLeafNode())
	{
		// For each object in our list of objects
		// Add the object to our list of results
		for each (GameObject* GO in objects)
		{
			results.push_back(GO);
		}
	}
	// 4. Else (i.e. we are not at leaf node)
	else {
		// if the object has partial fit
		if (index == PARTIAL_FIT)
		{
			// For each child node, retrieve objects from that node
			for each (Quadtree* node in nodes)
			{
				node->RetrieveNearbyObjects(object, results);
			}
		}
		// else, object has total fit, so retrieve objects from the specific node
		else
		{
			switch (index)
			{
			case TOP_RIGHT:
				nodes[1]->RetrieveNearbyObjects(object, results);
				break;
			case TOP_LEFT:
				nodes[0]->RetrieveNearbyObjects(object, results);
				break;
			case BOTTOM_RIGHT:
				nodes[3]->RetrieveNearbyObjects(object, results);
				break;
			case BOTTOM_LEFT:
				nodes[2]->RetrieveNearbyObjects(object, results);
				break;
			default:
				break;
			}
		}
	}
}

void Quadtree::Clear()
{
	// 1. If we are at a leaf node
	if (IsLeafNode())
	{
		// Clear our list of objects
		objects.clear();
	}
	// 2. Else (i.e. not a leaf node)
	else {
		// For each node
		// Delete the node
		// Set the node to null
		for (size_t i = 0; i < 4; i++)
		{
			nodes[i]->Clear();
			delete nodes[i];
			nodes[i] = nullptr;
		}
		
	}
}

void Quadtree::Split()
{
	// 1. Create and initialize variables for the extents of the sub-nodes.
	// (Extents of every sub-node will be half of the extents of the current node.)

	// 2. Create the four new nodes with centers located at the center of this node +/- the sub-node with and height.
	// NOTE: Maximum number of objects will remain the same for the subnodes.

	// NOTE: steps 1 and 2 are merged here

	//0 = TL (-,+), 1 = TR (+,+), 2 = BL (-,-), 3 = BR (+,-)
	nodes[0] = new Quadtree(BoundingRectangle(bounds.center + Vector2D(-(bounds.extents / 2).x, (bounds.extents / 2).y), bounds.extents / 2), maxObjects, maxTreeDepth, level + 1);
	nodes[1] = new Quadtree(BoundingRectangle(bounds.center + Vector2D((bounds.extents / 2).x, (bounds.extents / 2).y), bounds.extents / 2), maxObjects, maxTreeDepth, level + 1);
	nodes[2] = new Quadtree(BoundingRectangle(bounds.center + Vector2D(-(bounds.extents / 2).x, -(bounds.extents / 2).y), bounds.extents / 2), maxObjects, maxTreeDepth, level + 1);
	nodes[3] = new Quadtree(BoundingRectangle(bounds.center + Vector2D((bounds.extents / 2).x, -(bounds.extents / 2).y), bounds.extents / 2), maxObjects, maxTreeDepth, level + 1);
	

	// 3. For each object in the current node
	for (size_t i = 0; i < objects.size(); i++)
	{
		// Get the index of the object
		GameObject* obj = objects[i];
		Quadrants index = GetIndex(obj->GetComponent<Transform>()->GetBounds());
		
		switch (index)
		{
		// If it fits in a specific quadrant,
		// Add it to the appropriate node
		case TOP_RIGHT:
			nodes[1]->AddObject(obj);
			break;
		case TOP_LEFT:
			nodes[0]->AddObject(obj);
			break;
		case BOTTOM_RIGHT:
			nodes[3]->AddObject(obj);
			break;
		case BOTTOM_LEFT:
			nodes[2]->AddObject(obj);
			break;
		// If it's only a partial fit, for each sub-node
		// Add it to the sub-node
		case PARTIAL_FIT:
			for each (Quadtree* node in nodes)
			{
				node->AddObject(obj);
			}
			break;
		// If it is some other case then just ignore it
		default:
			break;
		}
	}

	// 4. Remove all objects from our object list; objects should only exist in leaf nodes.
	objects.clear();
}

Quadrants Quadtree::GetIndex(const BoundingRectangle & object)
{
	// 1. Compute the bounding rectangle for the object
	//        DONE ^

	// 2. Compare the bounds of the object with the bounds of the node.
	// If the object is not within bounds of this node
	// return OUT_OF_BOUNDS

	if (!RectangleRectangleIntersection(bounds, object))
	{
		return OUT_OF_BOUNDS;
	}

	// Now we know that fit is at least partial!
	// index = PARTIAL_FIT;

	Quadrants index = PARTIAL_FIT;

	// 3. Determine whether object can completely fit within the top quadrants
	// HINT: Compare the bottom of the object with the center of this node.
	bool isTopQuad = false;
	if (object.bottom > bounds.center.y)
	{
		//yes it fits within the top quads
		isTopQuad = true;
	}

	// 4. Determine whether object can completely fit within the bottom quadrants
	// HINT: Compare the top of the object with the center of this node.
	bool isBottomQuad = false;
	if (object.top <= bounds.center.y)
	{
		//yes it fits within the bottom quads
		isBottomQuad = true;
	}

	// 5. If it can fit within the left quadrants (similar to above)
	if (object.right < bounds.center.x)
	{
		// if it fits in top quadrants
		if (isTopQuad)
		{
			// index is top left
			index = TOP_LEFT;
		}
		// else if it fits in bottom quadrants
		else if (isBottomQuad)
		{
			// index is bottom left
			index = BOTTOM_LEFT;
		}
	}
	// 6. Else, if object can completely fit within the right quadrants
	else if (object.left >= bounds.center.x)
	{
		// if it fits in top quadrants
		if (isTopQuad)
		{
			// index is top right
			index = TOP_RIGHT;
		}
		// else if it fits in bottom quadrants
		else if (isBottomQuad)
		{
			// index is bottom right
			index = BOTTOM_RIGHT;
		}
	}

	// 7. Return the index
	return index;
}

bool Quadtree::IsLeafNode() const
{
	if (nodes[0] == nullptr)
	{
		return true;
	}

	return false;
}
