#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

class Renderer;
class Mesh;
class Node;

struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;

#include "Export.h"

class DllExport Importer{
public:
	Importer(Renderer& render);
	~Importer();
	bool importMesh(const std::string& rkFilename, Mesh& mesher);

	bool importScene(const std::string& rkFilename, Node& orkSceneRoot);

	void loadScene(aiNode* aiNode, Node& node, const aiScene* scene);
	void loadNode(aiNode* root, Node& node, const aiScene* scene);
	void loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material);
private:
	Renderer& _render;
	int materialCount;
};
#endif