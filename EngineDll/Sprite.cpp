#include "Sprite.h"

Sprite::Sprite()
	:
	_texture(NULL)
{
	_texturedVertex[0].x = -0.5f;	_texturedVertex[0].y = 0.5f;	_texturedVertex[0].z = 0.0f;
	_texturedVertex[1].x = 0.5f;	_texturedVertex[1].y = 0.5f;	_texturedVertex[1].z = 0.0f;
	_texturedVertex[2].x = -0.5f;	_texturedVertex[2].y = -0.5f;	_texturedVertex[2].z = 0.0f;
	_texturedVertex[3].x = 0.5f;	_texturedVertex[3].y = -0.5f;	_texturedVertex[3].z = 0.0f;

	_texturedVertex[0].u = 0.0f;		_texturedVertex[0].v = 0.0f;
	_texturedVertex[1].u = 1.0f;		_texturedVertex[1].v = 0.0f;
	_texturedVertex[2].u = 0.0f;		_texturedVertex[2].v = 1.0f;
	_texturedVertex[3].u = 1.0f;		_texturedVertex[3].v = 1.0f;
}

Sprite::~Sprite(){
	delete a;
	a = NULL;
}

void Sprite::setTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3){
	_texturedVertex[0].u = u0;		_texturedVertex[0].v = v0;
	_texturedVertex[1].u = u1;		_texturedVertex[1].v = v1;
	_texturedVertex[2].u = u2;		_texturedVertex[2].v = v2;
	_texturedVertex[3].u = u3;		_texturedVertex[3].v = v3;
}

void Sprite::setTexture(const Texture& texture){
	_texture = texture;
}

void Sprite::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(_texture);
	rkRenderer.setMatrix(transformationMatrix());
	rkRenderer.draw(_texturedVertex, ARRAY_SIZE(_texturedVertex));
}

void Sprite::setAnimation(Animation *animat){
	a = animat;
}

void Sprite::update(Timer& timer){
	if (!a)
		return;
	
	a->update(timer);
	currentFrame = a->currentFrame;

	if (currentFrame != lastFrame || currentFrame == 0)
	{
		setTextureCoordinates(a->frames[currentFrame].uvTextures[0].u, a->frames[currentFrame].uvTextures[0].v,
							  a->frames[currentFrame].uvTextures[1].u, a->frames[currentFrame].uvTextures[1].v,
							  a->frames[currentFrame].uvTextures[2].u, a->frames[currentFrame].uvTextures[2].v,
							  a->frames[currentFrame].uvTextures[3].u, a->frames[currentFrame].uvTextures[3].v);
		lastFrame = currentFrame;
	}
}