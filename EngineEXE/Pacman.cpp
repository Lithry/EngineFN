#include "Pacman.h"
#include "input.h"
#include "Camera.h"

#include <iostream>

void WASDController(Entity3D* object, Input& rkInput);
void KLController(Entity3D* object, Input& rkInput);
void RigLefUpDownController(Entity3D* object, Input& rkInput);

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(0.2f);

	debug1 = new ScreenText();
	debug1->create(0, 0, 1000, 1000, 25, "Arial", "DEBUG", false, rkRenderer);
	debug2 = new ScreenText();
	debug2->create(0, 60, 1000, 1000, 25, "Arial", "DEBUG", false, rkRenderer);

	root = new Node();

	Importer* importer = new Importer(rkRenderer);
	importer->importScene("Assets/Scene/2ObjScene.dae", *root);

	root->updateTransformation();

	min = new Mesh(rkRenderer);
	max = new Mesh(rkRenderer);

	importer->importMesh("Assets/Obj/Ball.obj", *min);
	importer->importMesh("Assets/Obj/Ball.obj", *max);

	min->setScale(0.2f, 0.2f, 0.2f);
	max->setScale(0.2f, 0.2f, 0.2f);

	Texture a = rkRenderer.loadTexture("Assets/Texture/Red.png", D3DCOLOR_XRGB(200, 200, 200));
	min->setTexture(a);
	Texture b = rkRenderer.loadTexture("Assets/Texture/Blue.png", D3DCOLOR_XRGB(200, 200, 200));
	min->setTexture(b);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);

	WASDController(root->findWithName("cube_pCube4"), rkInput);
	KLController(root->findWithName("pCube4"), rkInput);
	RigLefUpDownController(root, rkInput);
	
	int numNodes = 0;
	int numMeshes = 0;
	std::string text = "";

	root->draw(AABBFrustumCollision::PartialInside, cam->getFrustum(), text);
	
	min->setPos(root->findWithName("cube_pCube4")->getAABB().actualMin.x, root->findWithName("cube_pCube4")->getAABB().actualMin.y, root->findWithName("cube_pCube4")->getAABB().actualMin.z);
	max->setPos(root->findWithName("cube_pCube4")->getAABB().actualMax.x, root->findWithName("cube_pCube4")->getAABB().actualMax.y, root->findWithName("cube_pCube4")->getAABB().actualMax.z);

	min->draw(cam->getFrustum());
	max->draw(cam->getFrustum());

	debug1->setText(text);
	debug1->display(rkRenderer);
	
	/*debug1->setText("DEBUG\nNodes Dibujados: " + std::to_string(numNodes));
	debug1->display(rkRenderer);
	debug2->setText("Meshes Dibujados: " + std::to_string(numMeshes));
	debug2->display(rkRenderer);*/
}

void Pacman::deinit(){
}

void WASDController(Entity3D* object, Input& rkInput){
	static float speed = 1;
	
	if (rkInput.keyDown(Input::KEY_W)){
		object->setPosZ(object->posZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_S)){
		object->setPosZ(object->posZ() - speed);
	}

	if (rkInput.keyDown(Input::KEY_A)){
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_D)){
		object->setPosX(object->posX() - speed);
	}
}

void KLController(Entity3D* object, Input& rkInput){
	static float speed = 0.1;

	if (rkInput.keyDown(Input::KEY_K)){
		object->setScale(object->scaleX() + speed, object->scaleY() + speed, object->scaleZ() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_L)){
		object->setScale(object->scaleX() - speed, object->scaleY() - speed, object->scaleZ() - speed);
	}
}

void RigLefUpDownController(Entity3D* object, Input& rkInput){
	static float speed = 1;

	if (rkInput.keyDown(Input::KEY_UP)){
		object->setScaleY(object->scaleY() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_DOWN)){
		object->setScaleY(object->scaleY() - speed);
	}

	if (rkInput.keyDown(Input::KEY_RIGHT)){
		object->setPosX(object->posX() + speed);
	}
	else if (rkInput.keyDown(Input::KEY_LEFT)){
		object->setPosX(object->posX() - speed);
	}
}