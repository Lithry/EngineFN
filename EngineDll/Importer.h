#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

class Mesh;

#include "Export.h"

class DllExport Importer{
public:
	Importer();
	~Importer();
	bool importMesh(const std::string& rkFilename, Mesh& mesher);

	bool importScene(const std::string& rkFilename, Node& orkSceneRoot);
private:
};
#endif