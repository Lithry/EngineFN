#ifndef MESH_H
#define MESH_H

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#include <vector>
#include "Entity3D.h"
#include "VertexAndPrimitives.h"

class Renderer;
class VertexBuffer3D;
class IndexBuffer;

#define DllExport __declspec( dllexport )

class DllExport Mesh : public Entity3D{
public:
	Mesh(Renderer& rkRenderer);
	~Mesh();

	void setMeshData(const Vertex* pakVertices, Primitive ePrimitive,
		size_t uiVertexCount, const unsigned short* pusIndices,
		size_t uiIndexCount);
	void draw();
	void setTextureId(int iTextureId);

private:
	Renderer& render;
	VertexBuffer3D* vertexBuffer;
	IndexBuffer* indexBuffer;
	Primitive _primitiv;

	Vertex* vert;
};
#endif