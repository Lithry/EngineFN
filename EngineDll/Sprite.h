#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D.h"
#include "Animation.h"
#include "timer.h"

#define DllExport __declspec( dllexport )

class Sprite : public Entity2D{
public:
	DllExport Sprite();
	DllExport ~Sprite();
	DllExport void draw(Renderer& rkRenderer);
	
	DllExport void setTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	DllExport void setTexture(const Texture& texture);
	DllExport void setAnimation(Animation *animat);
	DllExport void update(Timer& timer);
private:
	int currentFrame;
	int lastFrame;
	
	Texture _texture;
	TexturedVertex _texturedVertex[4];
	Animation* a;
};
#endif