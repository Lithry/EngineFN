#include "Animation.h"

Animation::Animation()
	:
	currentTime(0),
	currentFrame(0),
	length(1000)
{}

Animation::~Animation(){}

void Animation::addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight){
	width = 2;
	heigth = 2;
	while ((tWidth - 0.1f) >= width){
		width *= 2;
	}

	while ((tHeight - 0.1f) >= heigth){
		heigth *= 2;
	}
	
	Frame toAdd(tWidth, tHeight, fPosX, fPosY, fWidth, fHeight);
	frames.push_back(toAdd);
}

void Animation::addFrame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight, int frameCount){
	float fPosXIndex = 0;
	width = 2;
	heigth = 2;
	while ((tWidth - 0.1f) >= width){
		width *= 2;
	}

	while ((tHeight - 0.1f) >= heigth){
		heigth *= 2;
	}

	for (int i = 0; i < frameCount; i++){
		Frame toAdd(tWidth, tHeight, fPosX + fPosXIndex, fPosY, fWidth, fHeight);
		frames.push_back(toAdd);
		fPosXIndex += fWidth;
	}
}

void Animation::update(Timer& t){
	currentTime += t.timeBetweenFrames();
	while (currentTime >= length){
		currentTime -= length;
	}
	frameLength = length / frames.size();
	currentFrame = static_cast<int>(currentTime / frameLength);
}