#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(2);

	mesh = new Mesh(rkRenderer);
	mesh->importObj("Assets/sword.obj");
	mesh->setPos(0, -10, 50);
	mesh->setRotationX(75);
	mesh->setScale(10, 10, 10);

	mesh2 = new Mesh(rkRenderer);
	mesh2->importObj("Assets/taurus.obj");
	mesh2->setPos(-50, -10, 100);
	mesh2->setScale(10, 10, 10);

	mesh3 = new Mesh(rkRenderer);
	mesh3->importObj("Assets/teapot.obj");
	mesh3->setPos(50, -10, 100);
	mesh3->setScale(1, 1, 1);

	mesh4 = new Mesh(rkRenderer);
	mesh4->importObj("Assets/Valla.obj");
	mesh4->setPos(0, -20, -20);
	mesh4->setScale(10, 10, 10);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	static float speedY = 1;
	static float speedX = 0.5;

	mesh->setRotationZ(mesh->rotationZ() + speedY);
	mesh->draw();
	mesh2->draw();
	mesh3->draw();
	mesh4->draw();
}

void Pacman::deinit(){
}