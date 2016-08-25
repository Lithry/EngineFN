
//---------------------------------------------------------------------------
#ifndef PG2_VERTEXBUFFER_H
#define PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
//#include "rendering/pg2_rendertypes.h" // Donde estan las primitivas
//---------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <cassert>
#include "Renderer.h"
//---------------------------------------------------------------------------
//class Renderer;
//---------------------------------------------------------------------------
#define DllExport __declspec( dllexport )

class DllExport VertexBuffer3D{
public:
	VertexBuffer3D (Renderer& rkRenderer, IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF);
	~VertexBuffer3D ();

	void bind ();
	void setVertexData (const void* pakVertices, size_t uiVertexCount);
	
	size_t vertexCount () const;

private:
	unsigned int m_uiFVF;
	size_t m_uiVertexSize;
	size_t m_uiVertexCount;

	LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer;
	IDirect3DDevice9* m_pkDevice;
	Renderer& m_rkRenderer;
};
//---------------------------------------------------------------------------
#include "pg2_vertexbuffer.inl"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif  // PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
