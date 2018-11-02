//------------------------------------------------------------------------------
//
// File Name:	MeshHelper.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MeshHelper.h"
#include <MeshFactory.h>
#include <Vertex.h>

Mesh * CreateTriangleMesh(const Color & color0, const Color & color1, const Color & color2)
{
	MeshFactory::GetInstance().AddTriangle(Vertex(Vector2D(-0.5,0.5), color0), Vertex(Vector2D(-0.5, -0.5), color1), Vertex(Vector2D(0.5, 0), color2));
	return MeshFactory::GetInstance().EndCreate();
}

Mesh * CreateQuadMesh(const Vector2D & textureSize, const Vector2D & extents)
{
	UNREFERENCED_PARAMETER(textureSize);
	UNREFERENCED_PARAMETER(extents);

	MeshFactory::GetInstance().AddTriangle(Vertex(Vector2D(-0.5, -0.5), Vector2D(0, 1)), Vertex(Vector2D(0.5, -0.5), Vector2D(1, 1)), Vertex(Vector2D(-0.5, 0.5), Vector2D(0, 0)));
	MeshFactory::GetInstance().AddTriangle(Vertex(Vector2D(0.5, -0.5), Vector2D(1, 1)), Vertex(Vector2D(0.5, 0.5), Vector2D(1, 0)), Vertex(Vector2D(-0.5, 0.5), Vector2D(0, 0)));
	return MeshFactory::GetInstance().EndCreate();
}
