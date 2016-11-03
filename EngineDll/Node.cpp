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