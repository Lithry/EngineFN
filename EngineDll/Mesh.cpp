#include "Mesh.h"

#include "Renderer.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)

Mesh::Mesh(Renderer& rkRenderer)
	:
	vertexBuffer(NULL),
	indexBuffer(NULL),
	render(rkRenderer),
	vert(new Vertex())
{

}

Mesh::~Mesh(){
	delete vertexBuffer;
	vertexBuffer = NULL;

	delete indexBuffer;
	indexBuffer = NULL;
}

void Mesh::setMeshData(const Vertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount){

	*vert = *pakVertices;
	vertexBuffer = render.createVertexBuffer(sizeof(Vertex), CUSTOMFVF);
	indexBuffer = render.createIndexBuffer();

	vertexBuffer->setVertexData(pakVertices, uiVertexCount);
	indexBuffer->setIndexData(pusIndices, uiIndexCount);
	
	render.setCurrentVertexBuffer(vertexBuffer);
	render.setCurrentIndexBuffer(indexBuffer);

	_primitiv = ePrimitive;
}

void Mesh::draw(){
	render.setMatrix(_transformationMatrix);
	render.drawCurrentBuffers(_primitiv);
}

void Mesh::setTextureId(int iTextureId){

}
