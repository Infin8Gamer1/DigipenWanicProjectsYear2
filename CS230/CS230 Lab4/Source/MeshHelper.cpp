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
	return nullptr;
}
