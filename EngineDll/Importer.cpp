#include "Importer.h"

#include <vector>
#include "VertexAndPrimitives.h"
#include "Mesh.h"
#include "AssImp\Importer.hpp"
#include "AssImp\scene.h"
#include "AssImp\postprocess.h"

#pragma comment(lib, "assimp.lib") 

Importer::Importer()
{}

Importer::~Importer(){

}

bool Importer::importMesh(const std::string& rkFilename, Mesh& mesher){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		const char* errors = importer.GetErrorString();
		return false;
	}

	aiMesh* meshs = *scene->mMeshes;

	Vertex* vert = new Vertex[meshs->mNumVertices];

	for (int i = 0; i< meshs->mNumVertices; i++)
	{
		vert[i].x = meshs->mVertices[i].x;
		vert[i].y = meshs->mVertices[i].y;
		vert[i].z = meshs->mVertices[i].z;
		vert[i].color = D3DCOLOR_XRGB(100, 100, 100);
	}
	
	int indexCount = meshs->mNumFaces * 3;
	unsigned short* indices = new unsigned short[indexCount];
	for (unsigned int i = 0; i< meshs->mNumFaces; i++)
	{
		indices[i * 3 + 0] = meshs->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = meshs->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = meshs->mFaces[i].mIndices[2];
	}

	mesher.setMeshData(vert, Primitive::TriangleList, meshs->mNumVertices, indices, indexCount);
	
	return true;
}