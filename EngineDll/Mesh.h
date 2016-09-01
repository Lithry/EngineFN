#ifndef MESH_H
#define MESH_H

#include "Renderer.h"

typedef TexturedVertex;
typedef Primitive;

#define DllExport __declspec( dllexport )

class DllExport Mesh{
public:
	Mesh(Renderer& rkRenderer);
	~Mesh();

	void setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
		size_t uiVertexCount, const unsigned short* pusIndices,
		size_t uiIndexCount);
	void draw();
	void setTextureId(int iTextureId);

private:
	Renderer render;
	VertexBuffer3D* vertexBuffer;
	IndexBuffer* indexBuffer;
};
#endif