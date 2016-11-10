#ifndef VERTEXANDPRIMITIVES_H
#define VERTEXANDPRIMITIVES_H

#include <windows.h>
#include "Export.h"

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

struct DllExport Vec3{
	float x, y, z;
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