#ifndef BSP_H
#define BSP_H

#include <vector>
#include "Importer.h"
//#include "Entity3D.h"
#include "Export.h"

#include "StructsAndEnums.h"

class Mesh;

class DllExport BSP{
public:
	BSP();
	~BSP();
	void addPlane(Plane plane);
	void addMesh(Mesh* mesh);
	void makePlane(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 position, Vec3 scale, Quaternion rotation);
	void updatePlanes();
	const std::vector<Plane> planes() const;
private:
	std::vector<Plane> _planes;
	std::vector<Mesh*> _meshes;
};
#endif