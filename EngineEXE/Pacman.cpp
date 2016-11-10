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

	//node1 = new Node();
	mesh = new Mesh(rkRenderer);
	Importer* importer = new Importer(rkRenderer);
	importer->importMesh("Assets/obj/cube.obj", *mesh);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	
	/*OPController(node1, rkInput);
	KLController(node1->findWithName("group1"), rkInput);
	NMController(node1->findWithName("pTorus1"), rkInput);

	node1->draw();*/
	OPController(mesh, rkInput);
	KLController(mesh, rkInput);

	mesh->draw();


	// DEBUG
	if (rkInput.keyDown(Input::KEY_Z)){
		std::cout << "MAX\nX: " << mesh->boundingBox()->max.x << " | Y: " << mesh->boundingBox()->max.y << " | Z: " << mesh->boundingBox()->max.z << std::endl;
		std::cout << "MIN\nX: " << mesh->boundingBox()->min.x << " | Y: " << mesh->boundingBox()->min.y << " | Z: " << mesh->boundingBox()->min.z << std::endl;
		std::cout << "===========================================================" << std::endl;
	}
}

void Pacman::deinit(){
}

void OPController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_O)){
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_P)){
		object->setPosX(object->posX() - speed);
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
		object->setRotationX(object->rotationX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_M)){
		object->setRotationX(object->rotationX() - speed);
	}
}