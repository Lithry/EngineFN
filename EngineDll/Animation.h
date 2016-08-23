#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"
#include "timer.h"

#define DllExport __declspec( dllexport )

class Animation{
public:
	DllExport Animation();
	DllExport ~Animation();
	DllExport void addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight);
	DllExport void addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight, int frameCount);
	DllExport void update(Timer& t);
	float currentTime;
	int currentFrame;
	float length;
	float frameLength;
	float width;
	float heigth;
	std::vector<Frame> frames;
};
#endif