#include "Frame.h"

Frame::Frame(float tWidth, float tHeight, float fPosX, float fPosY, float fWidth, float fHeight){
	uvTextures[0].u = (fPosX / tWidth);
	uvTextures[0].v = (fPosY / tHeight);

	uvTextures[1].u = ((fPosX + fWidth) / tWidth);
	uvTextures[1].v = (fPosY / tHeight);

	uvTextures[2].u = (fPosX / tWidth);
	uvTextures[2].v = ((fPosY + fHeight) / tHeight);

	uvTextures[3].u = ((fPosX + fWidth) / tWidth);
	uvTextures[3].v = ((fPosY + fHeight) / tHeight);
}

Frame::~Frame(){}