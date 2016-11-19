#include "Node.h"

#include "Mesh.h"

Node::Node(){}

Node::~Node(){}

void Node::addChild(Entity3D* pkChild){
	pkChild->setParent(this);
	_childs.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild){
	_childs.erase(find(_childs.begin(), _childs.end(), pkChild));
}

void Node::draw(){
	updateTransformation();
	updateBV();

	if (!_childs.empty()){
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw();
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