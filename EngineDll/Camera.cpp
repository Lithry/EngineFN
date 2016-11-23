#include "Camera.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

Camera::Camera(Renderer& rend)
	:
	_renderer(rend),
	_eye(new D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	_forward(new D3DXVECTOR3(0.0f, 0.0f, 1.0f)),
	_lookAt(new D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	_up(new D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
	_rigth(new D3DXVECTOR3(1.0f, 0.0f, 0.0f)),
	_left(new D3DXVECTOR3(-1.0f, 0.0f, 0.0f)),
	_view(new D3DXMATRIX),
	cameraSpeed(1.0f)
{
	for (size_t i = 0; i < 6; i++)
	{
		frustum.frustum[i] = new D3DXPLANE();
	}

	update();
}

Camera::~Camera(){
	delete _eye;
	_eye = NULL;
	delete _forward;
	_forward = NULL;
	delete _lookAt;
	_lookAt = NULL;
	delete _up;
	_up = NULL;
	delete _rigth;
	_rigth = NULL;
	delete _left;
	_left = NULL;
	
	for (size_t i = 0; i < 6; i++)
	{
		delete frustum.frustum[i];
		frustum.frustum[i] == NULL;
	}
}

bool Camera::init(){

	return true;
}

void Camera::roll(float angl){
	D3DXMATRIX* rollMat = new D3DXMATRIX();
	D3DXMatrixRotationAxis(rollMat, _forward, D3DXToRadian(angl));
	D3DXVec3TransformCoord(_rigth, _rigth, rollMat);
	D3DXVec3TransformCoord(_up, _up, rollMat);

	update();

	delete rollMat;
	rollMat = NULL;
}

void Camera::pitch(float angl){
	D3DXMATRIX* pitchMat = new D3DXMATRIX();
	D3DXMatrixRotationAxis(pitchMat, _rigth, D3DXToRadian(angl));
	D3DXVec3TransformCoord(_forward, _forward, pitchMat);

	update();

	delete pitchMat;
	pitchMat = NULL;
}

void Camera::yaw(float angl){
	D3DXMATRIX* yawMat = new D3DXMATRIX();
	D3DXMatrixRotationAxis(yawMat, _up, D3DXToRadian(angl));
	D3DXVec3TransformCoord(_forward, _forward, yawMat);
	D3DXVec3TransformCoord(_rigth, _rigth, yawMat);

	update();

	delete yawMat;
	yawMat = NULL;
}

void Camera::walk(float dist){
	*_eye += *_forward * dist;

	update();
}

void Camera::strafe(float dist){
	*_eye += *_rigth * dist;

	update();
}

void Camera::fly(float dist){
	*_eye += *_up * dist;

	update();
}

void Camera::update(){
	*_lookAt = *_eye + *_forward;

	D3DXMatrixLookAtLH(_view,
		_eye,
		_lookAt,
		_up);

	_renderer.setViewMatrix(*_view);

	updateFrustum();
}

void Camera::updateFrustum(){
	// http://www.rastertek.com/dx10tut16.html
	// Create the frustum matrix from the view matrix and updated projection matrix.
	D3DXMATRIX matrix;
	D3DXMatrixMultiply(&matrix, _view, _renderer.projectionMatrix());

	// Calculate near plane of frustum.
	frustum.frustum[0]->a = matrix._14 + matrix._13;
	frustum.frustum[0]->b = matrix._24 + matrix._23;
	frustum.frustum[0]->c = matrix._34 + matrix._33;
	frustum.frustum[0]->d = matrix._44 + matrix._43;
	D3DXPlaneNormalize(frustum.frustum[0], frustum.frustum[0]);

	// Calculate far plane of frustum.
	frustum.frustum[1]->a = matrix._14 - matrix._13;
	frustum.frustum[1]->b = matrix._24 - matrix._23;
	frustum.frustum[1]->c = matrix._34 - matrix._33;
	frustum.frustum[1]->d = matrix._44 - matrix._43;
	D3DXPlaneNormalize(frustum.frustum[1], frustum.frustum[1]);

	// Calculate left plane of frustum.
	frustum.frustum[2]->a = matrix._14 + matrix._11;
	frustum.frustum[2]->b = matrix._24 + matrix._21;
	frustum.frustum[2]->c = matrix._34 + matrix._31;
	frustum.frustum[2]->d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(frustum.frustum[2], frustum.frustum[2]);

	// Calculate right plane of frustum.
	frustum.frustum[3]->a = matrix._14 - matrix._11;
	frustum.frustum[3]->b = matrix._24 - matrix._21;
	frustum.frustum[3]->c = matrix._34 - matrix._31;
	frustum.frustum[3]->d = matrix._44 - matrix._41;
	D3DXPlaneNormalize(frustum.frustum[3], frustum.frustum[3]);

	// Calculate top plane of frustum.
	frustum.frustum[4]->a = matrix._14 - matrix._12;
	frustum.frustum[4]->b = matrix._24 - matrix._22;
	frustum.frustum[4]->c = matrix._34 - matrix._32;
	frustum.frustum[4]->d = matrix._44 - matrix._42;
	D3DXPlaneNormalize(frustum.frustum[4], frustum.frustum[4]);

	// Calculate bottom plane of frustum.
	frustum.frustum[5]->a = matrix._14 + matrix._12;
	frustum.frustum[5]->b = matrix._24 + matrix._22;
	frustum.frustum[5]->c = matrix._34 + matrix._32;
	frustum.frustum[5]->d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(frustum.frustum[5], frustum.frustum[5]);
}

const Frustum& Camera::getFrustum() const{
	return frustum;
}

void Camera::controls(Input& rkInput){
	if (rkInput.keyDown(Input::KEY_Q)){
		roll(cameraSpeed);
	}
	else if (rkInput.keyDown(Input::KEY_E)){
		roll(-cameraSpeed);
	}

	if (rkInput.keyDown(Input::KEY_SPACE)){
		fly(cameraSpeed);
	}
	else if (rkInput.keyDown(Input::KEY_LCONTROL)){
		fly(-cameraSpeed);
	}

	if (rkInput.keyDown(Input::KEY_W)){
		walk(cameraSpeed);
	}
	else if (rkInput.keyDown(Input::KEY_S)){
		walk(-cameraSpeed);
	}
	if (rkInput.keyDown(Input::KEY_A)){
		strafe(-cameraSpeed);
	}
	else if (rkInput.keyDown(Input::KEY_D)){
		strafe(cameraSpeed);
	}

	yaw(float(rkInput.mouseRelPosX()) / 8.0f);
	pitch(float(rkInput.mouseRelPosY()) / 8.0f);
}

void Camera::setCameraSpeed(float speed){
	cameraSpeed = speed;
}