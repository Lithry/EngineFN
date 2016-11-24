#include "Pacman.h"
#include "input.h"
#include "Camera.h"

#include <iostream>

void OPController(Entity3D* object, Input& rkInput);
void KLController(Entity3D* object, Input& rkInput);
void NMController(Entity3D* object, Input& rkInput);

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(0.2f);

	debug = new ScreenText();
	debug->create(0, 0, 1000, 1000, 25, "Arial", "DEBUG", false, rkRenderer);

	mesh = new Node();

	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/TP8Scene.dae", *mesh);

	mesh->updateTransformation();

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);

	OPController(mesh, rkInput);
	KLController(mesh, rkInput);
	NMController(mesh, rkInput);
	
	mesh->draw(cam->getFrustum());
	
	debug->setText("DEBUG\t Actual/Total\nNodes: \nMeshs:");
	debug->display(rkRenderer);
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
		object->setScaleY(object->scaleY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_L)){
		object->setScaleY(object->scaleY() - speed);
	}
}

void NMController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_N)){
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_M)){
		object->setPosZ(object->posZ() - speed);
	}
}