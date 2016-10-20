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
	render(rkRenderer)
{}

Mesh::~Mesh(){
	delete vertexBuffer;
	vertexBuffer = NULL;
	delete indexBuffer;
	indexBuffer = NULL;
}

void Mesh::setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount){

	vertexBuffer = render.createVertexBuffer(sizeof(TexturedVertex), TEXTUREFVF);
	indexBuffer = render.createIndexBuffer();

	vertexBuffer->setVertexData(pakVertices, uiVertexCount);
	indexBuffer->setIndexData(pusIndices, uiIndexCount);

	render.setCurrentVertexBuffer(vertexBuffer);
	render.setCurrentIndexBuffer(indexBuffer);

	_primitiv = ePrimitive;
}

void Mesh::draw(){
	render.setCurrentTexture(_texture);
	render.setCurrentVertexBuffer(vertexBuffer);
	render.setCurrentIndexBuffer(indexBuffer);
	render.setMatrix(_worldTransformationMatrix);
	render.drawCurrentBuffers(_primitiv);
}

void Mesh::setTextureId(int iTextureId){

}

bool Mesh::importObj(const std::string& objName/*, const std::string& textureName*/){
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

void Mesh::setTexture(const Texture& texture){
	_texture = texture;
}