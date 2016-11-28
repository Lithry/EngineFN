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
	Camera* cam;
	Importer* import;
	Node* root;
	ScreenText* debug1;
	ScreenText* debug2;

	Mesh* cube;
	Mesh* cube2;
	Node* nCube;
	Node* nCube2;

	Mesh* min;
	Mesh* max;
	Mesh* min2;
	Mesh* max2;
};
#endif