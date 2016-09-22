#ifndef QUAD_H
#define QUAD_H

#include "Export.h"
//#define DllExport __declspec( dllexport )

#include "Entity2D.h"

class DllExport Quad : public Entity2D{
public:
	Quad();
	~Quad();
	void draw(Renderer& rkRenderer);
private:
	Vertex* Vert;
};
#endif