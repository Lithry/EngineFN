#include "Node.h"

#include "StructsAndEnums.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

Node::Node(){}

Node::~Node(){}

void Node::addChild(Entity3D* pkChild){
	pkChild->setParent(this);
	_childs.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild){
	_childs.erase(find(_childs.begin(), _childs.end(), pkChild));
}

void Node::draw(const Frustum& rkFrustum){
	draw(AABBFrustumCollision::PartialInside, rkFrustum);
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum){
	updateTransformation();
	if (pCollision != AABBFrustumCollision::AllInside && pCollision != AABBFrustumCollision::AllOutside){
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision == AABBFrustumCollision::AllInside || pCollision == AABBFrustumCollision::PartialInside){
		if (!_childs.empty()){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(pCollision, rkFrustum);
			}
		}
	}
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text){
	updateTransformation();
	if (pCollision != AABBFrustumCollision::AllInside && pCollision != AABBFrustumCollision::AllOutside){
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision == AABBFrustumCollision::AllInside || pCollision == AABBFrustumCollision::PartialInside){
		if (pCollision == AABBFrustumCollision::AllInside)
			text = text + getName() + " (AllInside)\n";
		else
			text = text + getName() + " (PartialInside)\n";
		
		if (!_childs.empty()){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(pCollision, rkFrustum, text);
			}
		}
	}
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes){
	updateTransformation();
	if (pCollision != AABBFrustumCollision::AllInside && pCollision != AABBFrustumCollision::AllOutside){
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision == AABBFrustumCollision::AllInside || pCollision == AABBFrustumCollision::PartialInside){
		
		numNodes++;

		if (!_childs.empty()){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(pCollision, rkFrustum, numNodes, numMeshes);
			}
		}
	}
}

void Node::updateTransformation(){
	Entity3D::updateTransformation();

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateTransformation();
	}
}

Entity3D* Node::findWithName(std::string name){
	if (getName() == name){
		return this;
	}
	else{
		for (size_t i = 0; i < _childs.size(); i++){
			Entity3D* find = _childs[i]->findWithName(name);
			if (find != NULL) {
				return find;
			}
		}
		return NULL;
	}
}

const std::vector<Entity3D*>& Node::childs() const{
	return _childs;
}

void Node::updateBV(){
	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateBV();

		if (_childs[i]->getAABB().actualMin.x < getAABB().min.x){
			setBoundingBoxMinX(_childs[i]->getAABB().actualMin.x);
		}
		if (_childs[i]->getAABB().actualMin.y < getAABB().min.y){
			setBoundingBoxMinY(_childs[i]->getAABB().actualMin.y);
		}
		if (_childs[i]->getAABB().actualMin.z < getAABB().min.z){
			setBoundingBoxMinZ(_childs[i]->getAABB().actualMin.z);
		}

		if (_childs[i]->getAABB().actualMax.x > getAABB().max.x){
			setBoundingBoxMaxX(_childs[i]->getAABB().actualMax.x);
		}
		if (_childs[i]->getAABB().actualMax.y > getAABB().max.y){
			setBoundingBoxMaxY(_childs[i]->getAABB().actualMax.y);
		}
		if (_childs[i]->getAABB().actualMax.z > getAABB().max.z){
			setBoundingBoxMaxZ(_childs[i]->getAABB().actualMax.z);
		}

		setActualBoundingBoxMinX((getAABB().min.x + posX()) * scaleX());
		setActualBoundingBoxMaxX((getAABB().max.x + posX()) * scaleX());

		setActualBoundingBoxMinY((getAABB().min.y + posY()) * scaleY());
		setActualBoundingBoxMaxY((getAABB().max.y + posY()) * scaleY());

		setActualBoundingBoxMinZ((getAABB().min.z + posZ()) * scaleZ());
		setActualBoundingBoxMaxZ((getAABB().max.z + posZ()) * scaleZ());

		/*setActualBoundingBoxMinX((getAABB().min.x * scaleX()) + posX());
		setActualBoundingBoxMaxX((getAABB().max.x * scaleX()) + posX());

		setActualBoundingBoxMinY((getAABB().min.y * scaleY()) + posY());
		setActualBoundingBoxMaxY((getAABB().max.y * scaleY()) + posY());

		setActualBoundingBoxMinZ((getAABB().min.z * scaleZ()) + posZ());
		setActualBoundingBoxMaxZ((getAABB().max.z * scaleZ()) + posZ());*/

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
}

AABBFrustumCollision Node::checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max){
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