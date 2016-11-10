#include "Entity3D.h"
#include "Node.h"

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Entity3D::Entity3D()
	:
	_worldTransformationMatrix(new D3DXMATRIX()),
	_localTransformationMatrix(new D3DXMATRIX()),
	_posX(0.0f),
	_posY(0.0f),
	_posZ(0.0f),
	_rotationX(0.0f),
	_rotationY(0.0f),
	_rotationZ(0.0f),
	_scaleX(1.0f),
	_scaleY(1.0f),
	_scaleZ(1.0f),
	_parent(NULL),
	_texture(NULL),
	bBox(new AABB())
{
	updateLocalTransformation();
}

Entity3D::~Entity3D(){
	delete _localTransformationMatrix;
	_localTransformationMatrix = NULL;
	delete _worldTransformationMatrix;
	_worldTransformationMatrix = NULL;
	delete bBox;
	bBox = NULL;
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

void Entity3D::setRotation(float fRotationX, float fRotationY, float fRotationZ){
	_rotationX = fRotationX;
	_rotationY = fRotationY;
	_rotationZ = fRotationZ;

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

void Entity3D::setTexture(Texture texture){
	_texture = texture;
}

void Entity3D::setName(std::string name){
	_name = name;
}

const std::string Entity3D::getName(){
	return _name;
}

void Entity3D::updateLocalTransformation(){
	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	D3DXMATRIX rotationMatX;
	D3DXMatrixRotationX(&rotationMatX, D3DXToRadian(_rotationX));

	D3DXMATRIX rotationMatY;
	D3DXMatrixRotationY(&rotationMatY, D3DXToRadian(_rotationY));

	D3DXMATRIX rotationMatZ;
	D3DXMatrixRotationZ(&rotationMatZ, D3DXToRadian(_rotationZ));

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &traslatrionMat, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatX, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatY, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatZ, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &scaleMat, _localTransformationMatrix);
}

const Matrix& Entity3D::localMatrix() const{
	return _localTransformationMatrix;
}

const Matrix& Entity3D::worldMatrix() const{
	return _worldTransformationMatrix;
}

const Texture& Entity3D::texture() const{
	return _texture;
}

void Entity3D::updateTransformation(){
	if (_parent)
		D3DXMatrixMultiply(_worldTransformationMatrix, _localTransformationMatrix, _parent->worldMatrix());
	else
		_worldTransformationMatrix = _localTransformationMatrix;
}

void Entity3D::setParent(Node* pkParent){
	_parent = pkParent;
}