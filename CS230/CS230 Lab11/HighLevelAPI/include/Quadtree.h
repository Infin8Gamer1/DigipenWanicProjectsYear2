//------------------------------------------------------------------------------
//
// File Name:	Quadtree.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Shapes2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
typedef enum Quadrants : short Quadrants;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Binary space partitioning data structure that allows for
// retrieval of objects near other objects.
class Quadtree
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for quadtree.
	// Params:
	//   bounds   = The area encompassed by this node.
	//   level    = The level of this node in the tree. Child nodes will have a level of one less.
	//   maxObjectsPerNode = The maximum number of game objects in this node before it will be split.
	Quadtree(const BoundingRectangle& bounds, int maxObjects, int maxTreeDepth, int level = 0);

	// Destructor for quadtree. Calls Clear function.
	~Quadtree();

	// Draws each of the nodes in the tree (for debug purposes only).
	void Draw() const;

	// Adds an object to the tree
	// Params:
	//   object = The game object being added to the tree.
	void AddObject(GameObject* object);

	// Retrieve all objects from the tree that could collide with a given object.
	// Params:
	//   object  = The object for which we want to retrieve nearby objects.
	//   results = The list that stores the nearby objects.
	void RetrieveNearbyObjects(GameObject* object, std::vector<GameObject*>& results);

	// Remove all objects from the tree.
	void Clear();

	// returns a string that contains info about this node in the tree
	std::string GetNodeInfo();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Splits the contents of a node into four child nodes.
	void Split();

	// Determines which of the four child nodes that an object belongs in.
	// Params:
	//   object = The object for which we need to find the index.
	Quadrants GetIndex(const BoundingRectangle& object);

	// Determines whether this node can contain objects.
	bool IsLeafNode() const;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	Quadtree* nodes[4]; // The four branching nodes of this tree.
	std::vector<GameObject*> objects; // List of objects contained in this node.
	BoundingRectangle bounds;   // Bounding rectangle that defines the area of the node in world space.
	int level;		    // Level of this node in the tree.
	int maxObjects;   // The Maximum number of objects before you want to split
	int maxTreeDepth;
};

//------------------------------------------------------------------------------


