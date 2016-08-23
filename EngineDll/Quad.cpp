#include "Quad.h"

Quad::Quad()
	:
	Vert(new Vertex[4])
{
	Vert[0].x = -0.5;	Vert[0].y = 0.5;	Vert[0].z = 0.0f;
	Vert[1].x = 0.5;	Vert[1].y = 0.5;	Vert[1].z = 0.0f;
	Vert[2].x = -0.5;	Vert[2].y = -0.5;	Vert[2].z = 0.0f;
	Vert[3].x = 0.5;	Vert[3].y = -0.5;	Vert[3].z = 0.0f;

	Vert[0].color = D3DCOLOR_ARGB(255, 255, 0, 255);
	Vert[1].color = D3DCOLOR_ARGB(255, 100, 2, 50);
	Vert[2].color = D3DCOLOR_ARGB(255, 255, 88, 11);
	Vert[3].color = D3DCOLOR_ARGB(255, 11, 150, 20);

	updateLocalTransformation();
}

Quad::~Quad(){
	delete[] Vert;
	Vert = NULL;
}



void Quad::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(NULL);
	rkRenderer.setMatrix(_transformationMatrix);
	rkRenderer.draw(Vert);
}