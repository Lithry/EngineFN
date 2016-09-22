#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D.h"
#include "Animation.h"
#include "timer.h"

#include "Export.h"
//#define DllExport __declspec( dllexport )

class DllExport Sprite : public Entity2D{
public:
	Sprite();
	~Sprite();
	void draw(Renderer& rkRenderer);
	
	void setTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	void setTexture(const Texture& texture);
	void setAnimation(Animation *animat);
	void update(Timer& timer);
private:
	int currentFrame;
	int lastFrame;
	
	Texture _texture;
	TexturedVertex _texturedVertex[4];
	Animation* a;
};
#endif