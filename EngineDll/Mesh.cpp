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

void Mesh::draw(const Frustum& rkFrustum){
	draw(AABBFrustumCollision::PartialInside, rkFrustum);
}

void Mesh::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum){
	updateTransformation();
	updateBV();

	if (pCollision == AABBFrustumCollision::PartialInside){
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside){
		render.setCurrentTexture(texture());
		render.setCurrentVertexBuffer(vertexBuffer);
		render.setCurrentIndexBuffer(indexBuffer);
		render.setMatrix(worldMatrix());
		render.drawCurrentBuffers(_primitiv);
	}
}

void Mesh::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text){
	updateTransformation();
	updateBV();

	if (pCollision == AABBFrustumCollision::PartialInside){
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside){

		if (pCollision == AABBFrustumCollision::AllInside)
			text = text + "    MESH " + getName() + " (AllInside)\n";
		else
			text = text + "    MESH " + getName() + " (PartialInside)\n";

		render.setCurrentTexture(texture());
		render.setCurrentVertexBuffer(vertexBuffer);
		render.setCurrentIndexBuffer(indexBuffer);
		render.setMatrix(worldMatrix());
		render.drawCurrentBuffers(_primitiv);
	}
}

void Mesh::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes){
	updateTransformation();
	updateBV();

	if (pCollision == AABBFrustumCollision::PartialInside){
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside){

		numMeshes++;

		render.setCurrentTexture(texture());
		render.setCurrentVertexBuffer(vertexBuffer);
		render.setCurrentIndexBuffer(indexBuffer);
		render.setMatrix(worldMatrix());
		render.drawCurrentBuffers(_primitiv);
	}
}

void Mesh::setTextureId(int iTextureId){

}

VertexBuffer3D* Mesh::getVertexBuffer(){
	return vertexBuffer;
}

IndexBuffer* Mesh::getIndexBuffer(){
	return indexBuffer;
}

void Mesh::setTexture(const Texture& texture){
	Entity3D::setTexture(texture);
}

Entity3D* Mesh::findWithName(std::string name){
	if (getName() == name){
		return this;
	}
	else
		return NULL;
}

void Mesh::updateBV(){
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
	D3DXMatrixDecompose(&scale, &rot, &pos, worldMatrix());

	setActualBoundingBoxMinX((getAABB().min.x * scale.x) + pos.x);
	setActualBoundingBoxMinY((getAABB().min.y * scale.y) + pos.y);
	setActualBoundingBoxMinZ((getAABB().min.z * scale.z) + pos.z);

	setActualBoundingBoxMaxX((getAABB().max.x * scale.x) + pos.x);
	setActualBoundingBoxMaxY((getAABB().max.y * scale.y) + pos.y);
	setActualBoundingBoxMaxZ((getAABB().max.z * scale.z) + pos.z);
}

AABBFrustumCollision Mesh::checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max){
	int count = 0;
	Vec3 toCheck[8];

	toCheck[0].x = min.x; toCheck[1].x = min.x; toCheck[2].x = min.x; toCheck[3].x = min.x;
	toCheck[0].y = min.y; toCheck[1].y = min.y;	toCheck[2].y = max.y; toCheck[3].y = max.y;
	toCheck[0].z = min.z; toCheck[1].z = max.z;	toCheck[2].z = min.z; toCheck[3].z = max.z;

	toCheck[4].x = max.x; toCheck[5].x = max.x; toCheck[6].x = max.x; toCheck[7].x = max.x;
	toCheck[4].y = max.y; toCheck[5].y = max.y;	toCheck[6].y = min.y; toCheck[7].y = min.y;
	toCheck[4].z = max.z; toCheck[5].z = min.z;	toCheck[6].z = max.z; toCheck[7].z = min.z;

	for (size_t i = 0; i < 8; i++)
	{
		if (D3DXPlaneDotCoord(frustum.nearPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0 &&
			D3DXPlaneDotCoord(frustum.farPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0 &&
			D3DXPlaneDotCoord(frustum.leftPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0 &&
			D3DXPlaneDotCoord(frustum.rightPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0 &&
			D3DXPlaneDotCoord(frustum.topPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0 &&
			D3DXPlaneDotCoord(frustum.bottomPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0){
			count++;
		}
	}

	if (count == 8)
		return AABBFrustumCollision::AllInside;
	else if (count == 0)
		return AABBFrustumCollision::AllOutside;
	else
		return AABBFrustumCollision::PartialInside;
}