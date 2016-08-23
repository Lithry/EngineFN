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
	_view(new D3DXMATRIX)
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

void Camera::roll(){

}

void Camera::pitch(){

}

void Camera::yaw(){

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