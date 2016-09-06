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

void Mesh::setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount){

	_textureVertex = *pakVertices;
}

void Mesh::draw(){
	render.draw(_textureVertex, ARRAY_SIZE(_texturedVertex));
}

void Mesh::setTextureId(int iTextureId){

}