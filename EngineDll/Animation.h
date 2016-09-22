#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"
#include "timer.h"

#include "Export.h"
//#define DllExport __declspec( dllexport )

class DllExport Animation{
public:
	Animation();
	~Animation();
	void addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight);
	void addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight, int frameCount);
	void update(Timer& t);
	float currentTime;
	int currentFrame;
	float length;
	float frameLength;
	float width;
	float heigth;
	std::vector<Frame> frames;
};
#endif