#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Renderer.h"
#include "StructsAndEnums.h"

class Node;

#include "Export.h"

class DllExport Entity3D{
public:
	Entity3D();
	~Entity3D();
	void setPos(float fPosX, float fPosY, float fPosZ);
	void setPosX(float fPosX);
	void setPosY(float fPosY);
	void setPosZ(float fPosZ);
	void setRotation(float fRotationX, float fRotationY, float fRotationZ);
	void setRotationX(float fRotationX);
	void setRotationY(float fRotationY);
	void setRotationZ(float fRotationZ);
	void setScale(float fScaleX, float fScaleY, float fScaleZ);
	void setScaleX(float fScaleX);
	void setScaleY(float fScaleY);
	void setScaleZ(float fScaleZ);
	float posX() const;
	float posY() const;
	float posZ() const;
	float rotationX() const;
	float rotationY() const;
	float rotationZ() const;
	float scaleX() const;
	float scaleY() const;
	float scaleZ() const;

	void setName(std::string name);
	void setTexture(Texture texture);

	const std::string getName();

	const Matrix& localMatrix() const;
	const Matrix& worldMatrix() const;
	const Texture& texture() const;
	virtual void updateTransformation();
	void setParent(Node* pkParent);
	
	virtual void draw(const Frustum& rkFrustum) = 0;
	virtual void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum) = 0;
	virtual void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text) = 0;
	virtual void draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes) = 0;
	virtual Entity3D* findWithName(std::string name) = 0;

	Node* _parent;

	const AABB& getAABB() const;
	void setBoundingBoxMinX(float fMinX);
	void setBoundingBoxMaxX(float fMaxX);
	void setBoundingBoxMinY(float fMinY);
	void setBoundingBoxMaxY(float fMaxY);
	void setBoundingBoxMinZ(float fMinZ);
	void setBoundingBoxMaxZ(float fMaxZ);
	void setActualBoundingBoxMinX(float fMinX);
	void setActualBoundingBoxMaxX(float fMaxX);
	void setActualBoundingBoxMinY(float fMinY);
	void setActualBoundingBoxMaxY(float fMaxY);
	void setActualBoundingBoxMinZ(float fMinZ);
	void setActualBoundingBoxMaxZ(float fMaxZ);
	virtual void updateBV() = 0;

	virtual AABBFrustumCollision checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max) = 0;
private:
	float _posX;
	float _posY;
	float _posZ;
	float _rotationX;
	float _rotationY;
	float _rotationZ;
	float _scaleX;
	float _scaleY;
	float _scaleZ;

	AABB* bBox;

	std::string _name;

	Matrix _localTransformationMatrix;
	Matrix _worldTransformationMatrix;

	Texture _texture;

	void updateLocalTransformation();
};
#endif