#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

class Mesh;

#include "Export.h"
//#define DllExport __declspec( dllexport )

class DllExport Importer{
public:
	Importer();
	~Importer();
	bool importMesh(const std::string& rkFilename, Mesh& mesher);
private:
};
#endif