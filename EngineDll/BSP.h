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
	void makePlanes();
	const std::vector<Plane> planes() const;
	const std::vector<Mesh*> meshs() const;
private:
	std::vector<Plane> _planes;
	std::vector<Mesh*> _meshsToFormPlanes;
};
#endif