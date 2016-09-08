#include "Mesh.h"

#include "Renderer.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)

D3DPRIMITIVETYPE Primitives[Primitive::PrimitiveCount] = { D3DPT_POINTLIST,
														   D3DPT_LINELIST,
														   D3DPT_LINESTRIP,
														   D3DPT_TRIANGLELIST,
														   D3DPT_TRIANGLESTRIP,
														   D3DPT_TRIANGLEFAN };

Mesh::Mesh(Renderer& rkRenderer)
	:
	render(rkRenderer)
{
	vertexBuffer = render.createVertexBuffer(sizeof(TexturedVertex), TEXTUREFVF);
	indexBuffer = render.createIndexBuffer();
}

Mesh::~Mesh(){
	delete vertexBuffer;
	vertexBuffer = NULL;

	delete indexBuffer;
	indexBuffer = NULL;
}

void Mesh::setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount){

	vertexBuffer->setVertexData(pakVertices, uiVertexCount);
	indexBuffer->setIndexData(pusIndices, uiIndexCount);
	
	_primitiv = ePrimitive;

	_textureVertex.clear();
	_index.clear();

	for (int i = 0; i < uiVertexCount; i++)	{
		_textureVertex.push_back(pakVertices[i]);
	}

	for (int i = 0; i < uiIndexCount; i++)	{
		_index.push_back(pusIndices[i]);
	}
}

void Mesh::draw(){
	vertexBuffer->bind();
	indexBuffer->bind();
	
	int iPrimitiveCount = 0;

	if (Primitives[_primitiv] == D3DPT_POINTLIST){
		iPrimitiveCount = indexBuffer->indexCount();
	}
	else if (Primitives[_primitiv] == D3DPT_LINELIST){
		iPrimitiveCount = indexBuffer->indexCount() / 2;
	}
	else if (Primitives[_primitiv] == D3DPT_LINESTRIP){
		iPrimitiveCount = indexBuffer->indexCount() - 1;
	}
	else if (Primitives[_primitiv] == D3DPT_TRIANGLELIST){
		iPrimitiveCount = indexBuffer->indexCount() / 3;
	}
	else if (Primitives[_primitiv] == D3DPT_TRIANGLESTRIP){
		iPrimitiveCount = indexBuffer->indexCount() - 2;
	}
	else if (Primitives[_primitiv] == D3DPT_TRIANGLEFAN){
		iPrimitiveCount = indexBuffer->indexCount() - 2;
	}

	render.drawCurrentBuffers(_primitiv, indexBuffer->indexCount(), iPrimitiveCount);
}

void Mesh::setTextureId(int iTextureId){

}