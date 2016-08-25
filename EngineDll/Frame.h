#ifndef FRAME_H
#define FRAME_H

#include "Maths.h"

#define DllExport __declspec( dllexport )

class DllExport Frame{
public:
	Frame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight);
	~Frame();
	uvTexture uvTextures[4];
};
#endif