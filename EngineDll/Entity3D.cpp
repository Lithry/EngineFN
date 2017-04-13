#include "Entity3D.h"
#include "Node.h"
//#include <limits>
//#include <cstddef>

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Entity3D::Entity3D()
	:
	_worldTransformationMatrix(new D3DXMATRIX()),
	_localTransformationMatrix(new D3DXMATRIX()),
	_posX(0.0f),
	_posY(0.0f),
	_posZ(0.0f),
	_rotationW(1.0f),
	_rotationX(0.0f),
	_rotationY(0.0f),
	_rotationZ(0.0f),
	_rotationEulerX(0.0f),
	_rotationEulerY(0.0f),
	_rotationEulerZ(0.0f),
	_scaleX(1.0f),
	_scaleY(1.0f),
	_scaleZ(1.0f),
	_parent(NULL),
	_texture(NULL),
	bBox(new AABB())
{
	bBox->localTransformMatrix = new D3DXMATRIX();

	bBox->max.x = bBox->max.y = bBox->max.z = std::numeric_limits<float>::lowest();
	bBox->min.x = bBox->min.y = bBox->min.z = FLT_MAX;

	updateLocalTransformation();
}

Entity3D::~Entity3D() {
	delete _localTransformationMatrix;
	_localTransformationMatrix = NULL;
	delete _worldTransformationMatrix;
	_worldTransformationMatrix = NULL;
	delete bBox;
	bBox = NULL;
}

void Entity3D::setPos(float fPosX, float fPosY, float fPosZ) {
	_posX = fPosX;
	_posY = fPosY;
	_posZ = fPosZ;

	updateLocalTransformation();
}

void Entity3D::setPosX(float fPosX) {
	_posX = fPosX;

	updateLocalTransformation();
}

void Entity3D::setPosY(float fPosY) {
	_posY = fPosY;

	updateLocalTransformation();
}

void Entity3D::setPosZ(float fPosZ) {
	_posZ = fPosZ;

	updateLocalTransformation();
}

void Entity3D::setRotation(float fRotationW, float fRotationX, float fRotationY, float fRotationZ) {
	_rotationW = fRotationW;
	_rotationX = fRotationX;
	_rotationY = fRotationY;
	_rotationZ = fRotationZ;

	updateLocalTransformation();
}

void Entity3D::setRotationX(float fRotationX) {
	_rotationEulerX = fRotationX;

	updateLocalTransformation();
}

void Entity3D::setRotationY(float fRotationY) {
	_rotationEulerY = fRotationY;

	updateLocalTransformation();
}

void Entity3D::setRotationZ(float fRotationZ) {
	_rotationEulerZ = fRotationZ;

	updateLocalTransformation();
}

void Entity3D::setScale(float fScaleX, float fScaleY, float fScaleZ) {
	_scaleX = fScaleX;
	_scaleY = fScaleY;
	_scaleZ = fScaleZ;

	if (_scaleX < 0)
		_scaleX = 0;
	if (_scaleY < 0)
		_scaleY = 0;
	if (_scaleZ < 0)
		_scaleZ = 0;

	updateLocalTransformation();
}

void Entity3D::setScaleX(float fScaleX) {
	_scaleX = fScaleX;

	if (_scaleX < 0)
		_scaleX = 0;

	updateLocalTransformation();
}

void Entity3D::setScaleY(float fScaleY) {
	_scaleY = fScaleY;

	if (_scaleY < 0)
		_scaleY = 0;

	updateLocalTransformation();
}

void Entity3D::setScaleZ(float fScaleZ) {
	_scaleZ = fScaleZ;

	if (_scaleZ < 0)
		_scaleZ = 0;

	updateLocalTransformation();
}

float Entity3D::posX() const {
	return _posX;
}

float Entity3D::posY() const {
	return _posY;
}

float Entity3D::posZ() const {
	return _posZ;
}

float Entity3D::rotationX() const {
	return _rotationEulerX;
}

float Entity3D::rotationY() const {
	return _rotationEulerY;
}

float Entity3D::rotationZ() const {
	return _rotationEulerZ;
}

float Entity3D::scaleX() const {
	return _scaleX;
}

float Entity3D::scaleY() const {
	return _scaleY;
}

float Entity3D::scaleZ() const {
	return _scaleZ;
}

void Entity3D::setTexture(Texture texture) {
	_texture = texture;
}

void Entity3D::setName(std::string name) {
	_name = name;
}

const std::string Entity3D::getName() {
	return _name;
}

void Entity3D::updateLocalTransformation() {
	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	//D3DXMATRIX rotationMatX;
	//D3DXMatrixRotationX(&rotationMatX, D3DXToRadian(_rotationX));

	//D3DXMATRIX rotationMatY;
	//D3DXMatrixRotationY(&rotationMatY, D3DXToRadian(_rotationY));

	//D3DXMATRIX rotationMatZ;
	//D3DXMatrixRotationZ(&rotationMatZ, D3DXToRadian(_rotationZ));

	D3DXQUATERNION rotQuat(_rotationX, _rotationY, _rotationZ, _rotationW);
	D3DXQUATERNION rotEuler;
	D3DXQuaternionRotationYawPitchRoll(&rotEuler, _rotationEulerX, _rotationEulerY, _rotationEulerZ);

	D3DXMATRIX rotationMatQuat;
	D3DXMatrixRotationQuaternion(&rotationMatQuat, &rotQuat);

	D3DXMATRIX rotationMatEuler;
	D3DXMatrixRotationQuaternion(&rotationMatEuler, &rotEuler);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &traslatrionMat, _localTransformationMatrix);
	//D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatX, _localTransformationMatrix);
	//D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatY, _localTransformationMatrix);
	//D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatZ, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatQuat, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &rotationMatEuler, _localTransformationMatrix);
	D3DXMatrixMultiply(_localTransformationMatrix, &scaleMat, _localTransformationMatrix);
}

const Matrix& Entity3D::localMatrix() const {
	return _localTransformationMatrix;
}

const Matrix& Entity3D::worldMatrix() const {
	return _worldTransformationMatrix;
}

const Texture& Entity3D::texture() const {
	return _texture;
}

void Entity3D::updateTransformation() {
	if (_parent)
		D3DXMatrixMultiply(_worldTransformationMatrix, _localTransformationMatrix, _parent->worldMatrix());
	else
		_worldTransformationMatrix = _localTransformationMatrix;
}

void Entity3D::setParent(Node* pkParent) {
	_parent = pkParent;
}

// AABB
const AABB& Entity3D::getAABB() const {
	return *bBox;
}

void Entity3D::setBoundingBoxMinX(float fMinX) {
	bBox->min.x = fMinX;
}

void Entity3D::setBoundingBoxMaxX(float fMaxX) {
	bBox->max.x = fMaxX;
}

void Entity3D::setBoundingBoxMinY(float fMinY) {
	bBox->min.y = fMinY;
}

void Entity3D::setBoundingBoxMaxY(float fMaxY) {
	bBox->max.y = fMaxY;
}

void Entity3D::setBoundingBoxMinZ(float fMinZ) {
	bBox->min.z = fMinZ;
}

void Entity3D::setBoundingBoxMaxZ(float fMaxZ) {
	bBox->max.z = fMaxZ;
}

void Entity3D::setActualBoundingBoxMinX(float fMinX) {
	bBox->actualMin.x = fMinX;
}

void Entity3D::setActualBoundingBoxMaxX(float fMaxX) {
	bBox->actualMax.x = fMaxX;
}

void Entity3D::setActualBoundingBoxMinY(float fMinY) {
	bBox->actualMin.y = fMinY;
}

void Entity3D::setActualBoundingBoxMaxY(float fMaxY) {
	bBox->actualMax.y = fMaxY;
}

void Entity3D::setActualBoundingBoxMinZ(float fMinZ) {
	bBox->actualMin.z = fMinZ;
}

void Entity3D::setActualBoundingBoxMaxZ(float fMaxZ) {
	bBox->actualMax.z = fMaxZ;
}