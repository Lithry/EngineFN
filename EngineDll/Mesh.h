#ifndef MESH_H
#define MESH_H

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#include <vector>
#include "Entity3D.h"
#include "StructsAndEnums.h"

class Renderer;
class VertexBuffer3D;
class IndexBuffer;

#include "Export.h"

class DllExport Mesh : public Entity3D{
public:
	Mesh(Renderer& rkRenderer);
	~Mesh();

	void setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
		size_t uiVertexCount, const unsigned short* pusIndices,
		size_t uiIndexCount);

	void draw();
	void draw(const Frustum& rkFrustum);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text, int& polygonsOnScreen);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes);
	void draw(BSP* bsp, Vec3 cameraPos);
	void draw(BSPState pCollision, BSP* bsp, Vec3 cameraPos);

	void setTextureId(int iTextureId);

	void setTexture(const Texture& texture);
	void updateBV();

	AABBFrustumCollision checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max);

	Entity3D* findWithName(std::string name);
	void countPolygons(int& totalPolugons);
	
	BSPState checkBSP(BSP* bsp, Vec3 cameraPos, const Vec3& min, const Vec3& max);

	VertexBuffer3D* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	int polygons;
private:
	Renderer& render;
	VertexBuffer3D* vertexBuffer;
	IndexBuffer* indexBuffer;
	Primitive _primitiv;
	
};
#endif