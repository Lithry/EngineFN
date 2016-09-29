#include "Node.h"

#include "Mesh.h"

Node::Node(){}

Node::~Node(){}

void Node::addChild(Entity3D* pkChild){
	pkChild->setParent(this);
	_childs.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild){
	//////////////////////////////////////////////////////
	for (size_t i = 0; i < _childs.size(); i++){	////// Mirar
		if (_childs[i] == pkChild)					////// 
			_childs.erase(_childs.begin() + i);		////// 
	}												////// 
	//////////////////////////////////////////////////////
}

void Node::draw(){
	if (!_childs.empty()){
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw();
		}
	}
}

void Node::updateTransformation(){
	updateLocalTransformation();
	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateTransformation();
	}
}

const std::vector<Entity3D*>& Node::childs() const{
	return _childs;
}