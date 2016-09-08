#ifndef PACMAN_H
#define PACMAN_H

#include "Game.h"
#include "Quad.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Animation.h"
#include "ScreenText.h"
#include "Camera.h"
#include "Mesh.h"

class Pacman : public Game{
public:
	bool init(Renderer& rkRenderer);
	void frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer);
	void deinit();
private:
	TileMap tileMap;
	Vertex OurVertices[8];
	std::vector<Quad*> obstacle;
	Sprite background;
	Sprite player;
	Animation nada;
	Animation walk;

	Camera* cam;

	ScreenText text;
	ScreenText text2;
	ScreenText text3;
	std::string score;

	Mesh* mesh;
};
#endif