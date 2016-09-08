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
	player.setPosZ(10);
	player.setAnimation(&nada);
	Texture playerTexture = rkRenderer.loadTexture("Assets/BabyMario.png", D3DCOLOR_XRGB(255, 255, 255));
	player.setTexture(playerTexture);
	player.setAnimation(&nada);

	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(2);

	return true;*/

	mesh = new Mesh(rkRenderer);

	OurVertices[0].x = -0.5;	OurVertices[0].y = 0.5;		OurVertices[0].z = 0.0f;
	OurVertices[1].x = 0.5;		OurVertices[1].y = 0.5;		OurVertices[1].z = 0.0f;
	OurVertices[2].x = -0.5;	OurVertices[2].y = -0.5;	OurVertices[2].z = 0.0f;
	OurVertices[3].x = 0.5;		OurVertices[3].y = -0.5;	OurVertices[3].z = 0.0f;
	
	OurVertices[4].x = -0.5;	OurVertices[4].y = 0.5;		OurVertices[4].z = 0.5f;
	OurVertices[5].x = 0.5;		OurVertices[5].y = 0.5;		OurVertices[5].z = 0.5f;
	OurVertices[6].x = -0.5;	OurVertices[6].y = -0.5;	OurVertices[6].z = 0.5f;
	OurVertices[7].x = 0.5;		OurVertices[7].y = -0.5;	OurVertices[7].z = 0.5f;

	OurVertices[0].u = 0.0f;		OurVertices[0].v = 0.0f;
	OurVertices[1].u = 1.0f;		OurVertices[1].v = 0.0f;
	OurVertices[2].u = 0.0f;		OurVertices[2].v = 1.0f;
	OurVertices[3].u = 1.0f;		OurVertices[3].v = 1.0f;

	OurVertices[4].u = 0.0f;		OurVertices[4].v = 0.0f;
	OurVertices[5].u = 1.0f;		OurVertices[5].v = 0.0f;
	OurVertices[6].u = 0.0f;		OurVertices[6].v = 1.0f;
	OurVertices[7].u = 1.0f;		OurVertices[7].v = 1.0f;



	mesh->setMeshData(OurVertices, Primitive::TriangleStrip, 8,)
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
}

void Pacman::deinit(){
}