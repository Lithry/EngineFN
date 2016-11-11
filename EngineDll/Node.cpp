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
	}

	for (size_t i = 0; i < _childs.size(); i++)
	{
		if (_childs[i]->getAABB().actualMin.x < getAABB().actualMin.x){
			setActualBoundingBoxMinX(_childs[i]->getAABB().actualMin.x);
		}
		if (_childs[i]->getAABB().actualMin.y < getAABB().actualMin.y){
			setActualBoundingBoxMinY(_childs[i]->getAABB().actualMin.y);
		}
		if (_childs[i]->getAABB().actualMin.z < getAABB().actualMin.z){
			setActualBoundingBoxMinZ(_childs[i]->getAABB().actualMin.z);
		}

		if (_childs[i]->getAABB().actualMax.x > getAABB().actualMax.x){
			setActualBoundingBoxMaxX(_childs[i]->getAABB().actualMax.x);
		}
		if (_childs[i]->getAABB().actualMax.y > getAABB().actualMax.y){
			setActualBoundingBoxMaxY(_childs[i]->getAABB().actualMax.y);
		}
		if (_childs[i]->getAABB().actualMax.z > getAABB().actualMax.z){
			setActualBoundingBoxMaxZ(_childs[i]->getAABB().actualMax.z);
		}
	}
}