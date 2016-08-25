#ifndef FRAME_H
#define FRAME_H

struct uvTexture{
	float u, v;
};

#define DllExport __declspec( dllexport )

class DllExport Frame{
public:
	Frame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight);
	~Frame();
	uvTexture uvTextures[4];
};
#endif