#include "Entity3D.h"

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Entity3D::Entity3D()
	:
	_transformationMatrix(new D3DXMATRIX()),
	_posX(0),
	_posY(0),
	_posZ(0),
	_rotationX(0),
	_rotationY(0),
	_rotationZ(0),
	_scaleX(0),
	_scaleY(0),
	_scaleZ(0)
{}

Entity3D::~Entity3D(){

}

void Entity3D::setPos(float fPosX, float fPosY, float fPosZ){
	_posX = fPosX;
	_posY = fPosY;
	_posZ = fPosZ;

	updateLocalTransformation();
}

void Entity3D::setPosX(float fPosX){
	_posX = fPosX;

	updateLocalTransformation();
}

void Entity3D::setPosY(float fPosY){
	_posY = fPosY;

	updateLocalTransformation();
}

void Entity3D::setPosZ(float fPosZ){
	_posZ = fPosZ;

	updateLocalTransformation();
}

void Entity3D::setRotationX(float fRotationX){
	_rotationX = fRotationX;

	updateLocalTransformation();
}

void Entity3D::setRotationY(float fRotationY){
	_rotationY = fRotationY;

	updateLocalTransformation();
}

void Entity3D::setRotationZ(float fRotationZ){
	_rotationZ = fRotationZ;

	updateLocalTransformation();
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ){
	_scaleX = fScaleX;
	_scaleY = fScaleY;
	_scaleZ = fScaleZ;

	updateLocalTransformation();
}

void Entity3D::setScaleX(float fScaleX){
	_scaleX = fScaleX;

	updateLocalTransformation();
}

void Entity3D::setScaleY(float fScaleY){
	_scaleY = fScaleY;

	updateLocalTransformation();
}

void Entity3D::setScaleZ(float fScaleZ){
	_scaleZ = fScaleZ;

	updateLocalTransformation();
}

float Entity3D::posX() const{
	return _posX;
}

float Entity3D::posY() const{
	return _posY;
}

float Entity3D::posZ() const{
	return _posZ;
}

float Entity3D::rotationX() const{
	return _rotationX;
}

float Entity3D::rotationY() const{
	return _rotationY;
}

float Entity3D::rotationZ() const{
	return _rotationZ;
}

float Entity3D::scaleX() const{
	return _scaleX;
}

float Entity3D::scaleY() const{
	return _scaleY;
}

float Entity3D::scaleZ() const{
	return _scaleZ;
}

void Entity3D::updateLocalTransformation(){
	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	D3DXMATRIX rotationXMat;
	D3DXMatrixRotationX(&rotationXMat, D3DXToRadian(_rotationX));
	
	D3DXMATRIX rotationYMat;
	D3DXMatrixRotationY(&rotationYMat, D3DXToRadian(_rotationY));
	
	D3DXMATRIX rotationZMat;
	D3DXMatrixRotationZ(&rotationZMat, D3DXToRadian(_rotationZ));

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationXMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationYMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationZMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);
}