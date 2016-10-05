#ifndef QUAD_H
#define QUAD_H

#include "Entity2D.h"

#include "Export.h"

class DllExport Quad : public Entity2D{
public:
	Quad();
	~Quad();
	void draw(Renderer& rkRenderer);
private:
	Vertex* Vert;
};
#endif