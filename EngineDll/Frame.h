#ifndef FRAME_H
#define FRAME_H

struct uvTexture{
	float u, v;
};

#define DllExport __declspec( dllexport )

class Frame{
public:
	DllExport Frame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight);
	DllExport ~Frame();
	uvTexture uvTextures[4];
};
#endif