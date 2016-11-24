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

	debug1 = new ScreenText();
	debug1->create(0, 0, 1000, 1000, 25, "Arial", "DEBUG", false, rkRenderer);
	debug2 = new ScreenText();
	debug2->create(0, 60, 1000, 1000, 25, "Arial", "DEBUG", false, rkRenderer);

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
	
	int numNodes = 0;
	int numMeshes = 0;
	std::string text = "";

	mesh->draw(AABBFrustumCollision::PartialInside, cam->getFrustum(), text);
	
	debug1->setText(text);
	debug1->display(rkRenderer);
	
	/*debug1->setText("DEBUG\nNodes Dibujados: " + std::to_string(numNodes));
	debug1->display(rkRenderer);
	debug2->setText("Meshes Dibujados: " + std::to_string(numMeshes));
	debug2->display(rkRenderer);*/
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