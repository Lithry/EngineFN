#include "BSP.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

BSP::BSP() {}

BSP::~BSP() {}

void BSP::addPlane(Plane plane) {
	_planes.push_back(plane);
}

const std::vector<Plane> BSP::planes() const {
	return _planes;
}