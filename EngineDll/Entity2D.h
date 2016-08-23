#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Renderer.h"

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#define DllExport __declspec( dllexport )



class Entity2D{
public:
	enum CollisionResult
	{
		CollisionVerticalUp,
		CollisionVerticalDown,
		CollisionHorizontalRight,
		CollisionHorizontalLeft,
		NoCollision
	};

	DllExport Entity2D();
	DllExport ~Entity2D();
	DllExport void setPosX(float fPosX);
	DllExport void setPosY(float fPosY);
	DllExport void setPosZ(float fPosZ);
	DllExport void setRotation(float fRotation);
	DllExport void setScale(float fScaleX, float fScaleY);
	DllExport void flipNot();
	DllExport void Flip();
	DllExport CollisionResult checkCollision(Entity2D& toCheck);
	DllExport void returnToPreviusPos(float fPosX, float fPosY);
	DllExport void returnToPreviusPosH();
	DllExport void returnToPreviusPosV();
	DllExport float posX() const;
	DllExport float posY() const;
	DllExport float previusPosX() const;
	DllExport float previusPosY() const;
	DllExport float rotation() const;
	DllExport float scaleX() const;
	DllExport float scaleY() const;
	bool _enCollisionX;
	bool _enCollisionY;
protected:
	void updateLocalTransformation();
	float _posX;
	float _posY;
	float _posZ;
	float _previusPosX;
	float _previusPosY;
	float _rotation;
	float _scaleX;
	float _scaleY;
	bool _flip;

	Matrix _transformationMatrix;
};
#endif