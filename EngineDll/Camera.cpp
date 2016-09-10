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
	update();
}

Camera::~Camera(){
	delete _eye;
	_eye = NULL;
	delete _lookAt;
	_lookAt = NULL;
	delete _up;
	_up = NULL;
	delete _rigth;
	_rigth = NULL;
}

bool Camera::init(){

	return true;
}

void Camera::roll(float angl){
	D3DXMATRIX rollMat;
	D3DXMatrixRotationAxis(&rollMat, &*_forward, D3DXToRadian(angl));
	D3DXVec3TransformCoord(&*_rigth, &*_rigth, &rollMat);
	D3DXVec3TransformCoord(&*_up, &*_up, &rollMat);

	update();
}

void Camera::pitch(float angl){
	D3DXMATRIX pitchMat;
	D3DXMatrixRotationAxis(&pitchMat, &*_rigth, D3DXToRadian(angl));
	D3DXVec3TransformCoord(&*_forward, &*_forward, &pitchMat);

	update();
}

void Camera::yaw(float angl){
	D3DXMATRIX yawMat;
	D3DXMatrixRotationAxis(&yawMat, &*_up, D3DXToRadian(angl));
	D3DXVec3TransformCoord(&*_forward, &*_forward, &yawMat);
	D3DXVec3TransformCoord(&*_rigth, &*_rigth, &yawMat);

	update();
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

	D3DXMatrixLookAtLH(&*_view,
		&*_eye,
		&*_lookAt,
		&*_up);

	_renderer.setViewMatrix(*_view);
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

	yaw(rkInput.mouseRelPosX() / 8);
	pitch(rkInput.mouseRelPosY() / 8);
}

void Camera::setCameraSpeed(float speed){
	cameraSpeed = speed;
}