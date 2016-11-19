#ifndef CAMERA_H
#define CAMERA_H

#include "Renderer.h"
#include "input.h"



#include "Export.h"

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
	void updateFrustum();
	const Frustum& getFrustum() const;

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

	Frustum frustum;
};
#endif