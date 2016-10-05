#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Renderer.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#include "Export.h"

class DllExport Entity2D{
public:
	enum CollisionResult
	{
		CollisionVerticalUp,
		CollisionVerticalDown,
		CollisionHorizontalRight,
		CollisionHorizontalLeft,
		NoCollision
	};

	Entity2D();
	~Entity2D();
	void setPosX(float fPosX);
	void setPosY(float fPosY);
	void setPosZ(float fPosZ);
	void setRotation(float fRotation);
	void setScale(float fScaleX, float fScaleY);
	void flipNot();
	void Flip();
	CollisionResult checkCollision(Entity2D& toCheck);
	void returnToPreviusPos(float fPosX, float fPosY);
	void returnToPreviusPosH();
	void returnToPreviusPosV();
	float posX() const;
	float posY() const;
	float previusPosX() const;
	float previusPosY() const;
	float rotation() const;
	float scaleX() const;
	float scaleY() const;
	bool _enCollisionX;
	bool _enCollisionY;
protected:
	void updateLocalTransformation();
	float _posX;
	float _posY;
	float _posZ;
	float _previusPosX;
	float _previusPosY;
	float _previusPosZ;
	float _rotation;
	float _scaleX;
	float _scaleY;
	bool _flip;

	Matrix _transformationMatrix;
};
#endif