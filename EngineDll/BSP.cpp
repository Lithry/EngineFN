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

void BSP::addMesh(Mesh * mesh){
	_meshes.push_back(mesh);
}

void BSP::makePlane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 position, Vec3 scale, Quaternion rotation) {
	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, position.x, position.y, position.z);

	D3DXQUATERNION rotQuat(rotation.x, rotation.y, rotation.z, rotation.w);

	D3DXMATRIX rotationMatQuat;
	D3DXMatrixRotationQuaternion(&rotationMatQuat, &rotQuat);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);

	D3DXMATRIX* transformationMatrix = new D3DXMATRIX();
	D3DXMatrixIdentity(transformationMatrix);
	
	D3DXMatrixMultiply(transformationMatrix, &traslatrionMat, transformationMatrix);
	D3DXMatrixMultiply(transformationMatrix, &rotationMatQuat, transformationMatrix);
	D3DXMatrixMultiply(transformationMatrix, &scaleMat, transformationMatrix);

	D3DXVECTOR3* vec1 = new D3DXVECTOR3();
	D3DXVec3Normalize(vec1, new D3DXVECTOR3(v1.x, v1.y, v1.z));
	D3DXVECTOR3* vec2 = new D3DXVECTOR3();
	D3DXVec3Normalize(vec2, new D3DXVECTOR3(v2.x, v2.y, v2.z));
	D3DXVECTOR3* vec3 = new D3DXVECTOR3();
	D3DXVec3Normalize(vec3, new D3DXVECTOR3(v3.x, v3.y, v3.z));

	D3DXVec3TransformNormal(vec1, vec1, transformationMatrix);
	D3DXVec3TransformNormal(vec2, vec2, transformationMatrix);
	D3DXVec3TransformNormal(vec3, vec3, transformationMatrix);

	D3DXPLANE* plane = new D3DXPLANE();
	
	D3DXPlaneFromPoints(plane, vec1, vec2, vec3);

	//D3DXPlaneTransform(plane, plane, transformationMatrix);

	addPlane(plane);
}

void BSP::updatePlanes(){
	for (size_t i = 0; i < _planes.size(); i++)
	{
		D3DXPlaneTransform(_planes[i], _planes[i], _meshes[i]->worldMatrix());
	}
}

const std::vector<Plane> BSP::planes() const {
	return _planes;
}