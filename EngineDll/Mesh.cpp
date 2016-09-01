#include "Mesh.h"

#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)

Mesh::Mesh(Renderer& rkRenderer)
	:
	render(rkRenderer)
{
	vertexBuffer = render.createVertexBuffer(sizeof(TexturedVertex), TEXTUREFVF);
	indexBuffer = render.createIndexBuffer();
}

Mesh::~Mesh(){

}