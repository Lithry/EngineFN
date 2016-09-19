#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(10);

	mesh = new Mesh(rkRenderer);
	mesh->importObj("Assets/Valla.obj");
	mesh->setPos(0, 0, 0);
	mesh->setScale(500, 500, 500);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);
	static float speedY = 1;
	static float speedX = 0.5;

	mesh->draw();

	mesh->setRotationY(mesh->rotationY() + speedY);
	
	mesh->draw();
}

void Pacman::deinit(){
}