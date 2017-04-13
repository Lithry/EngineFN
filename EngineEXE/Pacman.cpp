#include "Pacman.h"
#include "input.h"
#include "Camera.h"

#include <iostream>

void WASDController(Entity3D* object, Input& rkInput);
void KLController(Entity3D* object, Input& rkInput);
void RigLefUpDownController(Entity3D* object, Input& rkInput);

bool Pacman::init(Renderer& rkRenderer) {
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(5);

	Importer* importer = new Importer(rkRenderer);

	debug1 = new ScreenText();
	debug1->create(0, 0, 1000, 1000, 14, "Arial", "DEBUG", false, rkRenderer);
	debug2 = new ScreenText();
	debug2->create(0, 60, 1000, 1000, 14, "Arial", "DEBUG", false, rkRenderer);

	root = new Node();
	//importer->importScene("Assets/Scene/tank.x", *root);
	//importer->importScene("Assets/Scene/bones_all.x", *root);
	//importer->importScene("Assets/Scene/sample_scene.dae", *root);
	importer->importScene("Assets/Scene/BSPTest3.dae", *root);
	root->setPosZ(500);
	root->setScale(10, 10, 10);
	root->updateTransformation();

	root->countPolygons(totalPolygons);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer) {
	cam->controls(rkInput);

	WASDController(root->findWithName("Inmovil1"), rkInput);
	//KLController(root->findWithName("Group001"), rkInput);
	//RigLefUpDownController(root->findWithName("Group001"), rkInput);

	int numNodes = 0;
	int numMeshes = 0;
	std::string text = "";
	int polygonsOnScreen = 0;

	root->draw(AABBFrustumCollision::PartialInside, cam->getFrustum(), text, polygonsOnScreen);

	text += "\nPolygons on Screen: " + std::to_string(polygonsOnScreen) + "\nTotal Polygons: " + std::to_string(totalPolygons);

	debug1->setText(text);
	debug1->display(rkRenderer);
}

void Pacman::deinit() {
}

void WASDController(Entity3D* object, Input& rkInput) {
	static float speed = 0.1;

	if (rkInput.keyDown(Input::KEY_W)) {
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_S)) {
		object->setPosZ(object->posZ() - speed);
	}

	if (rkInput.keyDown(Input::KEY_D)) {
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_A)) {
		object->setPosX(object->posX() - speed);
	}

	if (rkInput.keyDown(Input::KEY_Q)) {
		object->setRotationZ(object->rotationZ() + speed);
	}
	if (rkInput.keyDown(Input::KEY_E)) {
		object->setRotationZ(object->rotationZ() - speed);
	}
}

void KLController(Entity3D* object, Input& rkInput) {
	static float speed = 0.1;

	if (rkInput.keyDown(Input::KEY_K)) {
		object->setScale(object->scaleX() + speed, object->scaleY() + speed, object->scaleZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_L)) {
		object->setScale(object->scaleX() - speed, object->scaleY() - speed, object->scaleZ() - speed);
	}
}

void RigLefUpDownController(Entity3D* object, Input& rkInput) {
	static float speed = 10;

	if (rkInput.keyDown(Input::KEY_UP)) {
		object->setScaleY(object->scaleY() + (speed / 100));
	}
	else if (rkInput.keyDown(Input::KEY_DOWN)) {
		object->setScaleY(object->scaleY() - (speed / 100));
	}

	if (rkInput.keyDown(Input::KEY_RIGHT)) {
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_LEFT)) {
		object->setPosX(object->posX() - speed);
	}
}