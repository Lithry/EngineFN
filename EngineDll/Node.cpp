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

Entity3D& Node::findChild(std::string name){
	for (size_t i = 0; i < _childs.size(); i++){
		if (_childs[i]->name() == name){
			return *_childs[i];
		}
		//_childs[i]->findChild(name);
	}
}

const std::vector<Entity3D*>& Node::childs() const{
	return _childs;
}