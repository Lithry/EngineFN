#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Entity3D.h"
#include "Importer.h"

class Mesh;

#include "Export.h"

class DllExport Node : public Entity3D{
public:
	Node();
	~Node();
	void addChild(Entity3D* pkChild);
	void removeChild(Entity3D* pkChild);
	void updateTransformation();
	
	void draw(const Frustum& rkFrustum);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text);
	void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes);

	Entity3D* findWithName(std::string name);

	const std::vector<Entity3D*>& childs() const;

	void updateBV();
	AABBFrustumCollision checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max);
private:
	std::vector<Entity3D*> _childs;
};
#endif