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
#include "Importer.h"
#include "Node.h"

class Pacman : public Game{
public:
	bool init(Renderer& rkRenderer);
	void frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer);
	void deinit();
private:
	TileMap tileMap;
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

	Node* node1;

	Entity3D* child1;
	Entity3D* child2;


	Importer* import;
};
#endif