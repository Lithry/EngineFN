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

	if (pCollision != AABBFrustumCollision::AllInside && pCollision != AABBFrustumCollision::AllOutside){
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision == AABBFrustumCollision::AllInside || pCollision == AABBFrustumCollision::PartialInside){
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
	setActualBoundingBoxMinX((getAABB().min.x + posX()) * scaleX());
	setActualBoundingBoxMaxX((getAABB().max.x + posX()) * scaleX());

	setActualBoundingBoxMinY((getAABB().min.y + posY()) * scaleY());
	setActualBoundingBoxMaxY((getAABB().max.y + posY()) * scaleY());

	setActualBoundingBoxMinZ((getAABB().min.z + posZ()) * scaleZ());
	setActualBoundingBoxMaxZ((getAABB().max.z + posZ()) * scaleZ());

	// Check Escala Negativa
	if (getAABB().actualMin.x > getAABB().actualMax.x){
		float a = getAABB().actualMin.x;
		setActualBoundingBoxMinX(getAABB().actualMax.x);
		setActualBoundingBoxMaxX(a);
	}
	if (getAABB().actualMin.y > getAABB().actualMax.y){
		float a = getAABB().actualMin.y;
		setActualBoundingBoxMinY(getAABB().actualMax.y);
		setActualBoundingBoxMaxY(a);
	}
	if (getAABB().actualMin.z > getAABB().actualMax.z){
		float a = getAABB().actualMin.z;
		setActualBoundingBoxMinZ(getAABB().actualMax.z);
		setActualBoundingBoxMaxZ(a);
	}
}

AABBFrustumCollision Mesh::checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max){
	int count = 0;

	for (size_t i = 0; i < 6; i++)
	{

		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(min.x, min.y, min.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(min.x, min.y, max.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(min.x, max.y, min.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(min.x, max.y, max.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(max.x, max.y, max.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(max.x, max.y, min.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(max.x, min.y, max.z)) > 0.0f){
			count++;
		}
		if (D3DXPlaneDotCoord(frustum.frustum[i], &D3DXVECTOR3(max.x, min.y, min.z)) > 0.0f){
			count++;
		}

	}

	if (count == 48)
		return AABBFrustumCollision::AllInside;
	else if (count == 0)
		return AABBFrustumCollision::AllOutside;
	else
		return AABBFrustumCollision::PartialInside;
}