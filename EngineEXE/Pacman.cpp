#include "Pacman.h"
#include "input.h"
#include "Camera.h"

void OPController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_O)){
		object->setRotationY(object->rotationY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_P)){
		object->setRotationY(object->rotationY() - speed);
	}
}

void KLController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_K)){
		object->setRotationZ(object->rotationZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_L)){
		object->setRotationZ(object->rotationZ() - speed);
	}
}

void NMController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_N)){
		object->setRotationX(object->rotationX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_M)){
		object->setRotationX(object->rotationX() - speed);
	}
}

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(0.2f);

	node1 = new Node();
	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/Scene.dae", *node1);

	child1 = node1->childs()[0];
	child2 = node1->childs()[1];

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	
	OPController(node1, rkInput);
	KLController(child2, rkInput);
	NMController(child1, rkInput);

	node1->updateTransformation();
	node1->draw();
}

void Pacman::deinit(){
}