#include "Pacman.h"
#include "input.h"
#include "Camera.h"

void OPController(Entity3D* object, Input& rkInput);
void KLController(Entity3D* object, Input& rkInput);
void NMController(Entity3D* object, Input& rkInput);

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(0.2f);

	node1 = new Node();
	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/Scene.dae", *node1);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	
	OPController(node1, rkInput);
	KLController(node1->findWithName("group1"), rkInput);
	NMController(node1->findWithName("pTorus1"), rkInput);

	node1->draw();
}

void Pacman::deinit(){
}

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