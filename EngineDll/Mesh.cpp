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
	Matrix _transformationMatrix;
	_transformationMatrix = new D3DXMATRIX();

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, 0, 0, vert->z+4000);

	D3DXMATRIX rotationMat;
	D3DXMatrixRotationZ(&rotationMat, 0);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, vert->x, vert->y, vert->z);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);



	render.setMatrix(_transformationMatrix);
	render.drawCurrentBuffers(_primitiv);
}

void Mesh::setTextureId(int iTextureId){

}
