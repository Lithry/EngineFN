#ifndef CAMERA_H
#define CAMERA_H

#include "Renderer.h"
#include "input.h"

struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

#define DllExport __declspec( dllexport )

class Camera{
public:
	DllExport Camera(Renderer& rend);
	DllExport ~Camera();
	
	DllExport bool init();
	
	DllExport void roll(float angl);
	DllExport void pitch(float angl);
	DllExport void yaw(float angl);
	
	DllExport void walk(float dist);
	DllExport void strafe(float dist);
	DllExport void fly(float dist);

	DllExport void update();

	DllExport void controls(Input& rkInput);
	DllExport void setCameraSpeed(float speed);
private:
	Renderer _renderer;
	Vector3 _eye;
	Vector3 _forward;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _rigth;
	Matrix _view;
	float cameraSpeed;
};
#endif