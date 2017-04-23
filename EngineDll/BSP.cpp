#include "BSP.h"

#include "Mesh.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

BSP::BSP() {}

BSP::~BSP() {}

void BSP::addPlane(Plane plane) {
	_planes.push_back(plane);
}

void BSP::addMesh(Mesh* mesh) {
	_meshsToFormPlanes.push_back(mesh);
}

void BSP::makePlanes() {
	for (size_t i = 0; i < _meshsToFormPlanes.size(); i++) {
		D3DXQUATERNION* quatAngles = new D3DXQUATERNION();
		//D3DXQUATERNION* quatAnglesNormal;
		D3DXMatrixDecompose(NULL, quatAngles, NULL, _meshsToFormPlanes[i]->worldMatrix());
		float yaw = 0.0f, pitch = 0.0f, roll = 0.0f; // z	  y		x
		//D3DXQuaternionNormalize(quatAnglesNormal, quatAngles);
		D3DXQuaternionRotationYawPitchRoll(quatAngles, yaw, pitch, roll);
		if (yaw > 360) {
			float a = 360;
			while (a < yaw) {
				a += 360;
			}
			yaw = a - yaw;
		}
		if (pitch > 360) {
			float a = 360;
			while (a < pitch) {
				a += 360;
			}
			pitch = a - pitch;
		}
		if (roll > 360) {
			float a = 360;
			while (a < roll) {
				a += 360;
			}
			roll = a - roll;
		}
		


		}
}

const std::vector<Plane> BSP::planes() const {
	return _planes;
}

const std::vector<Mesh*> BSP::meshs() const {
	return _meshsToFormPlanes;
}