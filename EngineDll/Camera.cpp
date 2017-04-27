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
	frustum.nearPlane = new D3DXPLANE();
	frustum.farPlane = new D3DXPLANE();
	frustum.leftPlane = new D3DXPLANE();
	frustum.rightPlane = new D3DXPLANE();
	frustum.topPlane = new D3DXPLANE();
	frustum.bottomPlane = new D3DXPLANE();

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
	
	delete frustum.nearPlane;
	frustum.nearPlane = NULL;
	delete frustum.farPlane;
	frustum.farPlane = NULL;
	delete frustum.leftPlane;
	frustum.leftPlane = NULL;
	delete frustum.rightPlane;
	frustum.rightPlane = NULL;
	delete frustum.topPlane;
	frustum.topPlane = NULL;
	delete frustum.bottomPlane;
	frustum.bottomPlane = NULL;
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
	frustum.nearPlane->a = matrix._14 + matrix._13;
	frustum.nearPlane->b = matrix._24 + matrix._23;
	frustum.nearPlane->c = matrix._34 + matrix._33;
	frustum.nearPlane->d = matrix._44 + matrix._43;
	D3DXPlaneNormalize(frustum.nearPlane, frustum.nearPlane);

	// Calculate far plane of frustum.
	frustum.farPlane->a = matrix._14 - matrix._13;
	frustum.farPlane->b = matrix._24 - matrix._23;
	frustum.farPlane->c = matrix._34 - matrix._33;
	frustum.farPlane->d = matrix._44 - matrix._43;
	D3DXPlaneNormalize(frustum.farPlane, frustum.farPlane);

	// Calculate left plane of frustum.
	frustum.leftPlane->a = matrix._14 + matrix._11;
	frustum.leftPlane->b = matrix._24 + matrix._21;
	frustum.leftPlane->c = matrix._34 + matrix._31;
	frustum.leftPlane->d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(frustum.leftPlane, frustum.leftPlane);

	// Calculate right plane of frustum.
	frustum.rightPlane->a = matrix._14 - matrix._11;
	frustum.rightPlane->b = matrix._24 - matrix._21;
	frustum.rightPlane->c = matrix._34 - matrix._31;
	frustum.rightPlane->d = matrix._44 - matrix._41;
	D3DXPlaneNormalize(frustum.rightPlane, frustum.rightPlane);

	// Calculate top plane of frustum.
	frustum.topPlane->a = matrix._14 - matrix._12;
	frustum.topPlane->b = matrix._24 - matrix._22;
	frustum.topPlane->c = matrix._34 - matrix._32;
	frustum.topPlane->d = matrix._44 - matrix._42;
	D3DXPlaneNormalize(frustum.topPlane, frustum.topPlane);

	// Calculate bottom plane of frustum.
	frustum.bottomPlane->a = matrix._14 + matrix._12;
	frustum.bottomPlane->b = matrix._24 + matrix._22;
	frustum.bottomPlane->c = matrix._34 + matrix._32;
	frustum.bottomPlane->d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(frustum.bottomPlane, frustum.bottomPlane);
}

const Frustum& Camera::getFrustum() const{
	return frustum;
}

void Camera::controls(Input& rkInput){
		if (rkInput.keyDown(Input::KEY_NUMPAD7)){
			roll(cameraSpeed);
		}
		else if (rkInput.keyDown(Input::KEY_NUMPAD9)){
			roll(-cameraSpeed);
		}

		if (rkInput.keyDown(Input::KEY_NUMPAD1)){
			fly(cameraSpeed);
		}
		else if (rkInput.keyDown(Input::KEY_NUMPAD3)){
			fly(-cameraSpeed);
		}

		if (rkInput.keyDown(Input::KEY_NUMPAD8)){
			walk(cameraSpeed);
		}
		else if (rkInput.keyDown(Input::KEY_NUMPAD5)){
			walk(-cameraSpeed);
		}
		if (rkInput.keyDown(Input::KEY_NUMPAD4)){
			strafe(-cameraSpeed);
		}
		else if (rkInput.keyDown(Input::KEY_NUMPAD6)){
			strafe(cameraSpeed);
		}
	yaw(float(rkInput.mouseRelPosX()) / 8.0f);
	pitch(float(rkInput.mouseRelPosY()) / 8.0f);
}

void Camera::setCameraSpeed(float speed){
	cameraSpeed = speed;
}

Vec3 Camera::getCameraPosition() {
	Vec3 camPos;
	camPos.x = _eye->x; camPos.y = _eye->y; camPos.z = _eye->z;
	return camPos;
}
