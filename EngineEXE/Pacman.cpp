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

	mesh = new Node();
	

	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/2ObjScene.dae", *mesh);
	//Texture wood = rkRenderer.loadTexture("Assets/Texture/Wood.JPG", D3DCOLOR_XRGB(255, 255, 255));
	//mesh->setTexture(wood);
	mesh->updateTransformation();

	min = new Mesh(rkRenderer);
	max = new Mesh(rkRenderer);

	min->setScale(0.2f, 0.2f, 0.2f);
	max->setScale(0.2f, 0.2f, 0.2f);

	importer->importMesh("Assets/Obj/Ball.obj", *min);
	importer->importMesh("Assets/Obj/Ball.obj", *max);

	Texture red = rkRenderer.loadTexture("Assets/Texture/Red.png", D3DCOLOR_XRGB(255, 255, 255));
	min->setTexture(red);
	Texture blue = rkRenderer.loadTexture("Assets/Texture/Blue.png", D3DCOLOR_XRGB(255, 255, 255));
	max->setTexture(blue);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);

	OPController(mesh, rkInput);
	KLController(mesh, rkInput);
	NMController(mesh, rkInput);

	max->setPos(mesh->getAABB().actualMax.x, mesh->getAABB().actualMax.y, mesh->getAABB().actualMax.z);
	min->setPos(mesh->getAABB().actualMin.x, mesh->getAABB().actualMin.y, mesh->getAABB().actualMin.z);

	mesh->draw(cam->getFrustum());
	min->draw(cam->getFrustum());
	max->draw(cam->getFrustum());

	// DEBUG
	if (rkInput.keyDown(Input::KEY_Z)){
		std::cout << "MAX\nX: " << mesh->getAABB().actualMax.x << " | Y: " << mesh->getAABB().actualMax.y << " | Z: " << mesh->getAABB().actualMax.z << std::endl;
		std::cout << "MIN\nX: " << mesh->getAABB().actualMin.x << " | Y: " << mesh->getAABB().actualMin.y << " | Z: " << mesh->getAABB().actualMin.z << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "CUBE POS\nX: " << mesh->posX() << " | Y: " << mesh->posY() << " | Z: " << mesh->posZ() << std::endl;
		std::cout << "CUBE SCALE\nX: " << mesh->scaleX() << " | Y: " << mesh->scaleY() << " | Z: " << mesh->scaleZ() << std::endl;
		std::cout << "===========================================================" << std::endl;
	}
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