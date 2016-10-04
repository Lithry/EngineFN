#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(2);

	mesh = new Mesh(rkRenderer);
	mesh->importObj("Assets/obj/sword2.obj");
	mesh->setPos(0, 0, 0);
	mesh->setRotationX(75);
	mesh->setScale(3, 3, 3);

	mesh2 = new Mesh(rkRenderer);
	mesh2->importObj("Assets/obj/teapot.obj");
	mesh2->setPos(-50, -10, 100);
	mesh2->setScale(1, 1, 1);

	mesh3 = new Mesh(rkRenderer);
	mesh3->importObj("Assets/obj/valla.obj");
	mesh3->setPos(50, -10, 100);
	mesh3->setScale(1, 1, 1);

	node1 = new Node();
	node2 = new Node();
	
	node1->addChild(node2);
	node2->addChild(mesh);
	node2->addChild(mesh2);
	node1->addChild(mesh3);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	static float speedY = 1;
	static float speedX = 1;

	if (rkInput.keyDown(Input::KEY_K)){
		node1->setRotationY(node1->rotationY() - speedX);
	}
	else if (rkInput.keyDown(Input::KEY_L)){
		node1->setRotationY(node1->rotationY() + speedX);
	}

	if (rkInput.keyDown(Input::KEY_UP)){
		node1->setPos(node1->posX(), node1->posY() + speedX, node1->posZ());
	}
	else if (rkInput.keyDown(Input::KEY_DOWN)){
		node1->setPosY(node1->posY() - speedX);
	}
	
	node1->updateTransformation();
	node1->draw();
}

void Pacman::deinit(){
}