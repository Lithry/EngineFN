#ifndef MESH_H
#define MESH_H

#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#define DllExport __declspec( dllexport )

class DllExport Mesh{
public:
	Mesh();
	~Mesh();
private:
	VertexBuffer vertexBuffer;
};
#endif