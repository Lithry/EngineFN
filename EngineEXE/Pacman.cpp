#include "Pacman.h"
#include "input.h"
#include "Camera.h"

void numpadController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_NUMPAD8)){
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_NUMPAD5)){
		object->setPosZ(object->posZ() - speed);
	}
	if (rkInput.keyDown(Input::KEY_NUMPAD6)){
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_NUMPAD4)){
		object->setPosX(object->posX() - speed);
	}
	if (rkInput.keyDown(Input::KEY_ADD)){
		object->setPosY(object->posY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_SUBTRACT)){
		object->setPosY(object->posY() - speed);
	}
	if (rkInput.keyDown(Input::KEY_NUMPAD9)){
		object->setRotationY(object->rotationY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_NUMPAD7)){
		object->setRotationY(object->rotationY() - speed);
	}
	if (rkInput.keyDown(Input::KEY_NUMPAD1)){
		object->setRotationZ(object->rotationZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_NUMPAD3)){
		object->setRotationZ(object->rotationZ() - speed);
	}
}

void keyController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_U)){
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_J)){
		object->setPosZ(object->posZ() - speed);
	}
	if (rkInput.keyDown(Input::KEY_K)){
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_H)){
		object->setPosX(object->posX() - speed);
	}
	if (rkInput.keyDown(Input::KEY_O)){
		object->setPosY(object->posY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_L)){
		object->setPosY(object->posY() - speed);
	}
	if (rkInput.keyDown(Input::KEY_I)){
		object->setRotationY(object->rotationY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_Y)){
		object->setRotationY(object->rotationY() - speed);
	}
	if (rkInput.keyDown(Input::KEY_N)){
		object->setRotationZ(object->rotationZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_M)){
		object->setRotationZ(object->rotationZ() - speed);
	}
}

void upDownController9and0(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_0)){
		object->setPosY(object->posY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_9)){
		object->setPosY(object->posY() - speed);
	}
}

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(0.2f);

	node1 = new Node();
	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/SceneTexture.dae", *node1);

	child1 = node1->childs()[0];
	child2 = node1->childs()[1];

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	
	numpadController(child1, rkInput);

	
	

	node1->updateTransformation();
	node1->draw();
}

void Pacman::deinit(){
}