#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

class Renderer;
class Mesh;
class Node;
class BSP;

struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;
struct Vec3;

#include "Export.h"

class DllExport Importer{
public:
	Importer(Renderer& render);
	~Importer();
	bool importMesh(const std::string& rkFilename, Mesh& mesher);

	bool importScene(const std::string& rkFilename, Node& orkSceneRoot);
	bool importScene(const std::string& rkFilename, Node& orkSceneRoot, BSP* orkSceneBSP);

	void loadNode(aiNode* root, Node& node, const aiScene* scene);
	void loadNode(aiNode* root, Node& node, const aiScene* scene, BSP* bsp);
	void loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material);
	void loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material, bool& isPlane, BSP* bsp);
	void loadPlane(BSP* bsp);
private:
	Renderer& _render;
	int materialCount;
};
#endif