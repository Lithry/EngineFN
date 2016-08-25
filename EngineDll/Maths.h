#ifndef MATHS_H
#define MATHS_H

#include "vertexbuffer.h"

// Renderer
class Vertex{
public:
	float x, y, z;
	DWORD color;
};
struct TexturedVertex{
public:
	float x, y, z;
	float u, v;
};
struct D3DXMATRIX;
typedef D3DXMATRIX* Matrix;
struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;
#define NoTexture NULL

typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

// Frame
struct uvTexture{
	float u, v;
};

// Camera
struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

#endif