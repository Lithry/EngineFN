#include "Importer.h"

#include "AssImp\Importer.hpp"
#include "AssImp\scene.h"
#include "AssImp\postprocess.h"

Importer::Importer(){

}

Importer::~Importer(){

}

bool Importer::importMesh(const std::string& rkFilename, Mesh& orkMesh){
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);



	// If the import failed, report it
	if (!scene)
	{
		const char* errors = importer.GetErrorString();
		return false;
	}
	// Now we can access the file's contents. 
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}