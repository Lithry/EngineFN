#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Renderer.h"

#define DllExport __declspec( dllexport )

class DllExport Entity3D{
public:
	Entity3D();
	~Entity3D();
	void setPos(float fPosX, float fPosY, float fPosZ);
	void setPosX(float fPosX);
	void setPosY(float fPosY);
	void setPosZ(float fPosZ);
	void setRotationX(float fRotationX);
	void setRotationY(float fRotationY);
	void setRotationZ(float fRotationZ);
	void setScale(float fScaleX, float fScaleY, float fScaleZ);
	void setScaleX(float fScaleX);
	void setScaleY(float fScaleY);
	void setScaleZ(float fScaleZ);
	float posX() const;
	float posY() const;
	float posZ() const;
	float rotationX() const;
	float rotationY() const;
	float rotationZ() const;
	float scaleX() const;
	float scaleY() const;
	float scaleZ() const;
protected:
	float _posX;
	float _posY;
	float _posZ;
	float _rotationX;
	float _rotationY;
	float _rotationZ;
	float _scaleX;
	float _scaleY;
	float _scaleZ;

	Matrix _transformationMatrix;

	Texture _texture;

	void updateLocalTransformation();
};
#endif