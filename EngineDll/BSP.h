#ifndef BSP_H
#define BSP_H

#include <vector>
#include "Importer.h"

#include "Export.h"

#include "StructsAndEnums.h"

class DllExport BSP{
public:
	BSP();
	~BSP();
	void addPlane(Plane plane);
	const std::vector<Plane> planes() const;
private:
	std::vector<Plane> _planes;
};
#endif