#ifndef VERTEXANDPRIMITIVES_H
#define VERTEXANDPRIMITIVES_H

#include <windows.h>

#define DllExport __declspec( dllexport )

class DllExport Vertex{
public:
	float x, y, z;
	DWORD color;
};
struct DllExport TexturedVertex{
public:
	float x, y, z;
	float u, v;
};

enum Primitive{
	PointList = 0,
	LineList,
	LineStrip,
	TriangleList,
	TriangleStrip,
	TriangleFan,
	PrimitiveCount
};
#endif