#ifndef CAMERA_H
#define CAMERA_H

#include "Renderer.h"
#include "input.h"

struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

#define DllExport __declspec( dllexport )

class DllExport Camera{
public:
	Camera(Renderer& rend);
	~Camera();
	
	bool init();
	
	void roll(float angl);
	void pitch(float angl);
	void yaw(float angl);
	
	void walk(float dist);
	void strafe(float dist);
	void fly(float dist);

	void update();

	void controls(Input& rkInput);
	void setCameraSpeed(float speed);
private:
	Renderer _renderer;
	Vector3 _eye;
	Vector3 _forward;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _rigth;
	Vector3 _left;
	Matrix _view;
	float cameraSpeed;
};
#endif