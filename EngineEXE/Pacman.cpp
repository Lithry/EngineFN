#include "Pacman.h"
#include "input.h"
#include "Camera.h"

bool Pacman::init(Renderer& rkRenderer){
	cam = new Camera(rkRenderer);
	cam->setCameraSpeed(10);


	mesh = new Mesh(rkRenderer);

	float cube = 25;

	Vertex OurVertices[8];
	OurVertices[0].x = -cube;	OurVertices[0].y = cube;	OurVertices[0].z = -cube;	OurVertices[0].color = D3DCOLOR_XRGB(100, 0, 100);    // vertex 0
	OurVertices[1].x = cube;	OurVertices[1].y = cube;	OurVertices[1].z = -cube;	OurVertices[1].color = D3DCOLOR_XRGB(0, 200, 0);    // vertex 1
	OurVertices[2].x = -cube;	OurVertices[2].y = -cube;	OurVertices[2].z = -cube;	OurVertices[2].color = D3DCOLOR_XRGB(100, 0, 100);	 // 2
	OurVertices[3].x = cube;	OurVertices[3].y = -cube;	OurVertices[3].z = -cube;	OurVertices[3].color = D3DCOLOR_XRGB(0, 200, 0);  // 3
	OurVertices[4].x = -cube;	OurVertices[4].y = cube;	OurVertices[4].z = cube;	OurVertices[4].color = D3DCOLOR_XRGB(100, 0, 100);    // ...
	OurVertices[5].x = cube;	OurVertices[5].y = cube;	OurVertices[5].z = cube;	OurVertices[5].color = D3DCOLOR_XRGB(0, 200, 0);
	OurVertices[6].x = -cube;	OurVertices[6].y = -cube;	OurVertices[6].z = cube;	OurVertices[6].color = D3DCOLOR_XRGB(100, 0, 100);
	OurVertices[7].x = cube;	OurVertices[7].y = -cube;	OurVertices[7].z = cube;	OurVertices[7].color = D3DCOLOR_XRGB(0, 200, 0);

	unsigned short indices[] =
	{
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

	mesh = new Mesh(rkRenderer);
	int verticesSize = ARRAYSIZE(OurVertices);
	int indicesSize = ARRAYSIZE(indices);

	mesh->setMeshData(OurVertices, Primitive::TriangleList, verticesSize, indices, indicesSize);

	return true;
}

void Pacman::frame(Renderer& rkRenderer, Input& rkInput, Timer& rkTimer){
	cam->controls(rkInput);

	mesh->draw();
}

void Pacman::deinit(){
}