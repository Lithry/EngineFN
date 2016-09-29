#include "Mesh.h"

#include "Renderer.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"
#include "Importer.h"

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
	delete vert;
	vert = NULL;
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
	render.setCurrentVertexBuffer(vertexBuffer);
	render.setCurrentIndexBuffer(indexBuffer);
	render.setMatrix(_localTransformationMatrix);
	render.drawCurrentBuffers(_primitiv);
}

void Mesh::setTextureId(int iTextureId){

}

bool Mesh::importObj(const std::string& objName){
	Importer* import = new Importer();
	
	if (import->importMesh(objName, *this))
		return false;

	return true;
}

VertexBuffer3D* Mesh::getVertexBuffer(){
	return vertexBuffer;
}

IndexBuffer* Mesh::getIndexBuffer(){
	return indexBuffer;
}