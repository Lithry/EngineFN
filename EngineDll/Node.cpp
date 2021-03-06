#include "Node.h"

#include "StructsAndEnums.h"
#include "BSP.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

Node::Node() {}

Node::~Node() {}

void Node::addChild(Entity3D* pkChild) {
	pkChild->setParent(this);
	_childs.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild) {
	_childs.erase(find(_childs.begin(), _childs.end(), pkChild));
}

void Node::draw() {
	updateTransformation();

	if (!_childs.empty()) {
		for (size_t i = 0; i < _childs.size(); i++) {
			_childs[i]->draw();
		}
	}
}

void Node::draw(const Frustum& rkFrustum) {
	draw(AABBFrustumCollision::PartialInside, rkFrustum);
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum) {
	updateTransformation();

	if (pCollision == AABBFrustumCollision::PartialInside) {
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside) {
		if (!_childs.empty()) {
			for (size_t i = 0; i < _childs.size(); i++) {
				_childs[i]->draw(pCollision, rkFrustum);
			}
		}
	}
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text) {
	updateTransformation();

	if (pCollision == AABBFrustumCollision::PartialInside) {
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside) {
		if (pCollision == AABBFrustumCollision::AllInside)
			text = text + "NODE: " + getName() + " (AllInside)\n";
		else
			text = text + "NODE: " + getName() + " (PartialInside)\n";

		if (!_childs.empty()) {
			for (size_t i = 0; i < _childs.size(); i++) {
				_childs[i]->draw(pCollision, rkFrustum, text);
			}
		}
	}
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, std::string& text, int& polygonsOnScreen) {
	updateTransformation();

	if (pCollision == AABBFrustumCollision::PartialInside) {
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside) {
		if (pCollision == AABBFrustumCollision::AllInside)
			text = text + "NODE: " + getName() + " (AllInside)\n";
		else
			text = text + "NODE: " + getName() + " (PartialInside)\n";

		if (!_childs.empty()) {
			for (size_t i = 0; i < _childs.size(); i++) {
				_childs[i]->draw(pCollision, rkFrustum, text, polygonsOnScreen);
			}
		}
	}
}

void Node::draw(AABBFrustumCollision pCollision, const Frustum& rkFrustum, int& numNodes, int& numMeshes) {
	updateTransformation();

	if (pCollision == AABBFrustumCollision::PartialInside) {
		updateBV();
		pCollision = checkAABBtoFrustum(rkFrustum, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != AABBFrustumCollision::AllOutside) {

		numNodes++;

		if (!_childs.empty()) {
			for (size_t i = 0; i < _childs.size(); i++) {
				_childs[i]->draw(pCollision, rkFrustum, numNodes, numMeshes);
			}
		}
	}
}

void Node::draw(BSP * bsp, Vec3 cameraPos) {
	draw(BSPState::Inside, bsp, cameraPos);
}

void Node::draw(BSPState pCollision, BSP* bsp, Vec3 cameraPos) {
	updateTransformation();

	if (pCollision == BSPState::Inside) {
		pCollision = checkBSP(bsp, cameraPos, getAABB().actualMin, getAABB().actualMax);
	}

	if (pCollision != BSPState::Outside) {
		if (!_childs.empty()) {
			for (size_t i = 0; i < _childs.size(); i++) {
				_childs[i]->draw(pCollision, bsp, cameraPos);
			}
		}
	}
}

void Node::updateTransformation() {
	Entity3D::updateTransformation();

	for (size_t i = 0; i < _childs.size(); i++) {
		_childs[i]->updateTransformation();
	}
}

Entity3D* Node::findWithName(std::string name) {
	if (getName() == name) {
		return this;
	}
	else {
		for (size_t i = 0; i < _childs.size(); i++) {
			Entity3D* find = _childs[i]->findWithName(name);
			if (find != NULL) {
				return find;
			}
		}
		return NULL;
	}
}

void Node::countPolygons(int& totalPolugons) {
	for (size_t i = 0; i < _childs.size(); i++) {
		_childs[i]->countPolygons(totalPolugons);
	}
}

const std::vector<Entity3D*>& Node::childs() const {
	return _childs;
}

void Node::updateBV() {
	setActualBoundingBoxMinX(FLT_MAX);
	setActualBoundingBoxMinY(FLT_MAX);
	setActualBoundingBoxMinZ(FLT_MAX);

	setActualBoundingBoxMaxX(std::numeric_limits<float>::lowest());
	setActualBoundingBoxMaxY(std::numeric_limits<float>::lowest());
	setActualBoundingBoxMaxZ(std::numeric_limits<float>::lowest());

	for (size_t i = 0; i < _childs.size(); i++) {
		_childs[i]->updateBV();

		if (_childs[i]->getAABB().actualMin.x < getAABB().actualMin.x) {
			setActualBoundingBoxMinX(_childs[i]->getAABB().actualMin.x);
		}
		if (_childs[i]->getAABB().actualMin.y < getAABB().actualMin.y) {
			setActualBoundingBoxMinY(_childs[i]->getAABB().actualMin.y);
		}
		if (_childs[i]->getAABB().actualMin.z < getAABB().actualMin.z) {
			setActualBoundingBoxMinZ(_childs[i]->getAABB().actualMin.z);
		}

		if (_childs[i]->getAABB().actualMax.x > getAABB().actualMax.x) {
			setActualBoundingBoxMaxX(_childs[i]->getAABB().actualMax.x);
		}
		if (_childs[i]->getAABB().actualMax.y > getAABB().actualMax.y) {
			setActualBoundingBoxMaxY(_childs[i]->getAABB().actualMax.y);
		}
		if (_childs[i]->getAABB().actualMax.z > getAABB().actualMax.z) {
			setActualBoundingBoxMaxZ(_childs[i]->getAABB().actualMax.z);
		}
	}
}

AABBFrustumCollision Node::checkAABBtoFrustum(const Frustum& frustum, const Vec3& min, const Vec3& max) {
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
			D3DXPlaneDotCoord(frustum.bottomPlane, &D3DXVECTOR3(toCheck[i].x, toCheck[i].y, toCheck[i].z)) > 0) {
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

BSPState Node::checkBSP(BSP* bsp, Vec3 cameraPos, const Vec3& min, const Vec3& max) {
	updateBV();
	BSPState state = BSPState::Inside;
	int count = 0;
	Vec3 toCheck[8];

	toCheck[0].x = min.x; toCheck[1].x = min.x; toCheck[2].x = min.x; toCheck[3].x = min.x;
	toCheck[0].y = min.y; toCheck[1].y = min.y;	toCheck[2].y = max.y; toCheck[3].y = max.y;
	toCheck[0].z = min.z; toCheck[1].z = max.z;	toCheck[2].z = min.z; toCheck[3].z = max.z;

	toCheck[4].x = max.x; toCheck[5].x = max.x; toCheck[6].x = max.x; toCheck[7].x = max.x;
	toCheck[4].y = max.y; toCheck[5].y = max.y;	toCheck[6].y = min.y; toCheck[7].y = min.y;
	toCheck[4].z = max.z; toCheck[5].z = min.z;	toCheck[6].z = max.z; toCheck[7].z = min.z;

	for (size_t i = 0; i < bsp->planes().size(); i++) {
		float cameraSide = D3DXPlaneDotCoord(bsp->planes()[i], &D3DXVECTOR3(cameraPos.x, cameraPos.y, cameraPos.z));
		if (state == BSPState::Inside) {
			count = 0;
			if (cameraSide < 0) {
				for (size_t j = 0; j < 8; j++) {
					if (D3DXPlaneDotCoord(bsp->planes()[i], &D3DXVECTOR3(toCheck[j].x, toCheck[j].y, toCheck[j].z)) > 0) {
						count++;
					}
				}
				if (count == 8)
					state = BSPState::Outside;
			}
			else {
				for (size_t j = 0; j < 8; j++) {
					if (D3DXPlaneDotCoord(bsp->planes()[i], &D3DXVECTOR3(toCheck[j].x, toCheck[j].y, toCheck[j].z)) < 0) {
						count++;
					}
				}
				if (count == 8)
					state = BSPState::Outside;
			}
		}
	}
	return state;
}
