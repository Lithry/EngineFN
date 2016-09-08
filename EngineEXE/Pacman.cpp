#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	tileMap.importTileMap("Assets/test4.tmx", rkRenderer);

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
	cam->setCameraSpeed(2);


	/*mesh = new Mesh(rkRenderer);

	unsigned short indices[36] = {
		0, 1, 2, 0, 2, 3, //front
		4, 5, 6, 4, 6, 7, //right
		8, 9, 10, 8, 10, 11, //back
		12, 13, 14, 12, 14, 15, //left
		16, 17, 18, 16, 18, 19, //upper
		20, 21, 22, 20, 22, 23 }; //bottom

	// Front
	OurVertices[0].x = -1;		OurVertices[0].y = -1;		OurVertices[0].z = 1;
	OurVertices[1].x = 1;		OurVertices[1].y = -1;		OurVertices[1].z = 1;
	OurVertices[2].x = 1;		OurVertices[2].y = 1;		OurVertices[2].z = 1;
	OurVertices[3].x = -1;		OurVertices[3].y = 1;		OurVertices[3].z = 1;
	// Right
	OurVertices[4].x = 1;		OurVertices[4].y = 1;		OurVertices[4].z = 1;
	OurVertices[5].x = 1;		OurVertices[5].y = 1;		OurVertices[5].z = -1;
	OurVertices[6].x = 1;		OurVertices[6].y = -1;		OurVertices[6].z = -1;
	OurVertices[7].x = 1;		OurVertices[7].y = -1;		OurVertices[7].z = 1;
	// Back
	OurVertices[8].x = -1;		OurVertices[8].y = -1;		OurVertices[8].z = -1;
	OurVertices[9].x = 1;		OurVertices[9].y = -1;		OurVertices[9].z = -1;
	OurVertices[10].x = 1;		OurVertices[10].y = 1;		OurVertices[10].z = -1;
	OurVertices[11].x = -1;		OurVertices[11].y = 1;		OurVertices[11].z = -1;
	// Left
	OurVertices[12].x = -1;		OurVertices[12].y = -1;		OurVertices[12].z = -1;
	OurVertices[13].x = 1;		OurVertices[13].y = -1;		OurVertices[13].z = -1;
	OurVertices[14].x = 1;		OurVertices[14].y = 1;		OurVertices[14].z = -1;
	OurVertices[15].x = -1;		OurVertices[15].y = 1;		OurVertices[15].z = -1;
	// Upper
	OurVertices[16].x = 1;		OurVertices[16].y = 1;		OurVertices[16].z = 1;
	OurVertices[17].x = -1;		OurVertices[17].y = 1;		OurVertices[17].z = 1;
	OurVertices[18].x = -1;		OurVertices[18].y = 1;		OurVertices[18].z = -1;
	OurVertices[19].x = 1;		OurVertices[19].y = 1;		OurVertices[19].z = -1;
	//Bottom
	OurVertices[20].x = -1;		OurVertices[20].y = -1;		OurVertices[20].z = -1;
	OurVertices[21].x = 1;		OurVertices[21].y = -1;		OurVertices[21].z = -1;
	OurVertices[22].x = 1;		OurVertices[22].y = -1;		OurVertices[22].z = 1;
	OurVertices[23].x = -1;		OurVertices[23].y = -1;		OurVertices[23].z = 1;

	OurVertices[0].u = 0.0f;		OurVertices[0].v = 0.0f;
	OurVertices[1].u = 1.0f;		OurVertices[1].v = 0.0f;
	OurVertices[2].u = 0.0f;		OurVertices[2].v = 1.0f;
	OurVertices[3].u = 1.0f;		OurVertices[3].v = 1.0f;

	OurVertices[4].u = 0.0f;		OurVertices[4].v = 0.0f;
	OurVertices[5].u = 1.0f;		OurVertices[5].v = 0.0f;
	OurVertices[6].u = 0.0f;		OurVertices[6].v = 1.0f;
	OurVertices[7].u = 1.0f;		OurVertices[7].v = 1.0f;

	OurVertices[8].u = 0.0f;		OurVertices[8].v = 0.0f;
	OurVertices[9].u = 1.0f;		OurVertices[9].v = 0.0f;
	OurVertices[10].u = 0.0f;		OurVertices[10].v = 1.0f;
	OurVertices[11].u = 1.0f;		OurVertices[11].v = 1.0f;

	OurVertices[12].u = 0.0f;		OurVertices[12].v = 0.0f;
	OurVertices[13].u = 1.0f;		OurVertices[13].v = 0.0f;
	OurVertices[14].u = 0.0f;		OurVertices[14].v = 1.0f;
	OurVertices[15].u = 1.0f;		OurVertices[15].v = 1.0f;

	OurVertices[16].u = 0.0f;		OurVertices[16].v = 0.0f;
	OurVertices[17].u = 1.0f;		OurVertices[17].v = 0.0f;
	OurVertices[18].u = 0.0f;		OurVertices[18].v = 1.0f;
	OurVertices[19].u = 1.0f;		OurVertices[19].v = 1.0f;

	OurVertices[20].u = 0.0f;		OurVertices[20].v = 0.0f;
	OurVertices[21].u = 1.0f;		OurVertices[21].v = 0.0f;
	OurVertices[22].u = 0.0f;		OurVertices[22].v = 1.0f;
	OurVertices[23].u = 1.0f;		OurVertices[23].v = 1.0f;

	/*WORD indices[36] = {
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
	};*/


	//mesh->setMeshData(OurVertices, Primitive::TriangleList, 24, indices, 36);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	static float fSpeed = 3.0f;
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
	text3.display(rkRenderer);

	//mesh->draw();
}

void Pacman::deinit(){
	/*delete mesh;
	mesh = NULL;*/
}