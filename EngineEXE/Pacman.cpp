#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	/*tileMap.importTileMap("Assets/test4.tmx", rkRenderer);

	text.create(5, 5, 400, 100, 20, "Arial", "Hola", false, rkRenderer);
	text2.create(5, 30, 300, 100, 20, "Arial", "UserName: Loki", false, rkRenderer);
	text3.create(5, 55, 400, 100, 20, "Arial", "Password: 3.14", false, rkRenderer);

	nada.length = 0.6f * 1000;
	nada.addFrame(440, 336, 304, 73, 33, 33);

	walk.length = 0.5f * 1000;
	walk.addFrame(440, 336, 208, 75, 33, 33);
	walk.addFrame(440, 336, 208, 108, 33, 33);
	walk.addFrame(440, 336, 208, 141, 33, 33);

	// Player scale, position, texture and animation seting
	player.setScale(50, 50);
	player.setPosX(-150);
	player.setPosY(60);
	player.setPosZ(40);
	player.setAnimation(&nada);
	Texture playerTexture = rkRenderer.loadTexture("Assets/BabyMario.png", D3DCOLOR_XRGB(255, 255, 255));
	player.setTexture(playerTexture);
	player.setAnimation(&nada);

	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(2);*/


	mesh = new Mesh(rkRenderer);

	
	float cube = 500;

	OurVertices[0].x = -cube;		OurVertices[0].y = cube;		OurVertices[0].z = -cube;	OurVertices[0].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[1].x = cube;		OurVertices[1].y = cube;		OurVertices[1].z = -cube;	OurVertices[1].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[2].x = -cube;		OurVertices[2].y = -cube;		OurVertices[2].z = -cube;	OurVertices[2].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[3].x = cube;		OurVertices[3].y = -cube;		OurVertices[3].z = -cube;	OurVertices[3].color = D3DCOLOR_XRGB(0, 0, 255);

	OurVertices[4].x = -cube;		OurVertices[4].y = cube;		OurVertices[4].z = cube;	OurVertices[4].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[5].x = cube;		OurVertices[5].y = cube;		OurVertices[5].z = cube;	OurVertices[5].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[6].x = -cube;		OurVertices[6].y = -cube;		OurVertices[6].z = cube;	OurVertices[6].color = D3DCOLOR_XRGB(0, 0, 255);
	OurVertices[7].x = cube;		OurVertices[7].y = -cube;		OurVertices[7].z = cube;	OurVertices[7].color = D3DCOLOR_XRGB(0, 0, 255);
	
	

	unsigned short indices[36] = {
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};


	

	mesh->setPosX(0);
	mesh->setPosY(0);
	mesh->setPosZ(0);
	mesh->setScale(100, 100, 100);
	mesh->setMeshData(OurVertices, Primitive::TriangleList, ARRAYSIZE(OurVertices), indices, ARRAYSIZE(indices));

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	/*static float fSpeed = 3.0f;
	static int i = 0;

	cam->controls(rkInput);

	player.setAnimation(&nada);

	if (rkInput.keyDown(Input::KEY_RIGHT)){
			player.setPosX(player.posX() + fSpeed);
			player.setAnimation(&walk);
			player.flipNot();
			i++;
	}
	else if (rkInput.keyDown(Input::KEY_LEFT)){
			player.setPosX(player.posX() - fSpeed);
			player.setAnimation(&walk);
			player.Flip();
			i++;
	}

	if (rkInput.keyDown(Input::KEY_UP)){
			player.setPosY(player.posY() + fSpeed);
			player.setAnimation(&walk);
			i++;
	}
	else if (rkInput.keyDown(Input::KEY_DOWN)){
			player.setPosY(player.posY() - fSpeed);
			player.setAnimation(&walk);
			i++;
	}

	// Limits Loop
	if (player.posX() < -550)
		player.setPosX(550);
	if (player.posX() > 550)
		player.setPosX(-550);

	tileMap.draw(rkRenderer);
	tileMap.checkCollision(player);

	player.update(rkTimer);
	player.draw(rkRenderer);
	
	score = "Score: " + std::to_string(i);
	text.setText(score);
	text.display(rkRenderer);
	text2.display(rkRenderer);
	text3.display(rkRenderer);*/

	mesh->draw();
}

void Pacman::deinit(){
	delete mesh;
	mesh = NULL;
}