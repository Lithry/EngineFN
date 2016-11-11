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

	mesh = new Mesh(rkRenderer);
	

	Importer* importer = new Importer(rkRenderer);
	importer->importMesh("Assets/Obj/Cube.obj", *mesh);
	Texture wood = rkRenderer.loadTexture("Assets/Texture/Wood.JPG", D3DCOLOR_XRGB(255, 255, 255));
	mesh->setTexture(wood);
	mesh->updateTransformation();

	min = new Mesh(rkRenderer);
	max = new Mesh(rkRenderer);

	min->setScale(0.2, 0.2, 0.2);
	max->setScale(0.2, 0.2, 0.2);

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

	max->setPos(mesh->boundingBox()->actualMax.x, mesh->boundingBox()->actualMax.y, mesh->boundingBox()->actualMax.z);
	min->setPos(mesh->boundingBox()->actualMin.x, mesh->boundingBox()->actualMin.y, mesh->boundingBox()->actualMin.z);

	mesh->draw();
	min->draw();
	max->draw();

	// DEBUG
	if (rkInput.keyDown(Input::KEY_Z)){
		std::cout << "MAX\nX: " << mesh->boundingBox()->actualMax.x << " | Y: " << mesh->boundingBox()->actualMax.y << " | Z: " << mesh->boundingBox()->actualMax.z << std::endl;
		std::cout << "MIN\nX: " << mesh->boundingBox()->actualMin.x << " | Y: " << mesh->boundingBox()->actualMin.y << " | Z: " << mesh->boundingBox()->actualMin.z << std::endl;
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
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_M)){
		object->setPosZ(object->posZ() - speed);
	}
}