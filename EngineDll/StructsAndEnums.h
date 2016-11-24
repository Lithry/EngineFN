#ifndef STRUCTSANDENUMS_H
#define STRUCTSANDENUMS_H

#include <windows.h>
#include <vector>
#include "Export.h"

// Others
struct DllExport Vec3{
	float x, y, z;
};

// Renderer
struct D3DXMATRIX;
typedef D3DXMATRIX* Matrix;
struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;
#define NoTexture NULL

typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

struct IDirect3D9;
struct IDirect3DDevice9;

class VertexBuffer3D;
class IndexBuffer;

typedef D3DXMATRIX* Matrix;

struct DllExport Vertex{
	float x, y, z;
	DWORD color;
};
struct DllExport TexturedVertex{
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

// Entity3D
// http://www.miguelcasillas.com/?mcportfolio=collision-detection-c
struct DllExport AABB{
	Vec3 min, max, actualMin, actualMax;
	Matrix scaleMatrix;
};
enum AABBFrustumCollision{
	AllInside = 0,
	PartialInside,
	AllOutside
};

// Camera
struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;
struct D3DXPLANE;
typedef D3DXPLANE* Plane;

struct DllExport Frustum{
	Plane nearPlane;
	Plane farPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane topPlane;
	Plane bottomPlane;
};
#endif