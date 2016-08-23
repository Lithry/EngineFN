#ifndef CAMERA_H
#define CAMERA_H

#include "Renderer.h"
struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

#define DllExport __declspec( dllexport )

/*struct Vector3{
	float x, y, z;
};*/

class Camera{
public:
	DllExport Camera(Renderer& rend);
	DllExport ~Camera();
	
	DllExport bool init();
	
	DllExport void roll();
	DllExport void pitch();
	DllExport void yaw();
	
	DllExport void walk(float dist);
	DllExport void strafe(float dist);
	DllExport void fly(float dist);

	DllExport void update();
private:
	Renderer _renderer;
	Vector3 _eye;
	Vector3 _forward;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _rigth;
	Matrix _view;
};
#endif