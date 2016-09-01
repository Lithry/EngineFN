#ifndef MESH_H
#define MESH_H

#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

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
	VertexBuffer3D vertexBuffer;
};
#endif