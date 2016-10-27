#include "Importer.h"

#include <vector>
#include "Renderer.h"
#include "VertexAndPrimitives.h"
#include "Mesh.h"
#include "Node.h"
#include "AssImp\Importer.hpp"
#include "AssImp\scene.h"
#include "AssImp\postprocess.h"

#pragma comment(lib, "assimp.lib") 

Importer::Importer(Renderer& render)
	:
	_render(render),
	materialCount(0)
{}

Importer::~Importer(){

}

bool Importer::importMesh(const std::string& rkFilename, Mesh& mesher){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_Triangulate);

	if (!scene)
	{
		const char* errors = importer.GetErrorString();
		return false;
	}

	aiMesh* meshs = *scene->mMeshes;

	TexturedVertex* vert = new TexturedVertex[meshs->mNumVertices];

	for (size_t i = 0; i < meshs->mNumVertices; i++)
	{
		vert[i].x = meshs->mVertices[i].x;
		vert[i].y = meshs->mVertices[i].y;
		vert[i].z = meshs->mVertices[i].z;

		if (meshs->HasTextureCoords(0)){
			vert[i].u = meshs->mTextureCoords[0][i].x;
			vert[i].v = meshs->mTextureCoords[0][i].y;
		}
	}

	int indexCount = meshs->mNumFaces * 3;
	unsigned short* indices = new unsigned short[indexCount];
	for (unsigned int i = 0; i < meshs->mNumFaces; i++)
	{
		indices[i * 3 + 0] = meshs->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = meshs->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = meshs->mFaces[i].mIndices[2];
	}

	mesher.setMeshData(vert, Primitive::TriangleList, meshs->mNumVertices, indices, indexCount);

	return true;
}

bool Importer::importScene(const std::string& rkFilename, Node& orkSceneRoot){
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

	aiNode* root = scene->mRootNode;
	loadScene(root, orkSceneRoot, scene);
	loadNode(root, orkSceneRoot, scene);

	return true;
}

void Importer::loadScene(aiNode* aiNode, Node& node, const aiScene* scene){
	
}

void Importer::loadNode(aiNode* root, Node& node, const aiScene* scene){

	for (size_t i = 0; i < root->mNumMeshes; i++)
	{
		Mesh* newMesh = new Mesh(_render);
		node.addChild(newMesh);
		aiMesh* aiMesh = scene->mMeshes[root->mMeshes[i]];
		aiMaterial* pMaterial = scene->mMaterials[root->mMeshes[i]];

		loadMesh(aiMesh, newMesh, pMaterial);
	}

	for (size_t i = 0; i < root->mNumChildren; i++)
	{
		Node* newNode = new Node();
		node.addChild(newNode);

		loadNode(root->mChildren[i], *newNode, scene);

	}
}

void Importer::loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material){
	TexturedVertex* vert = new TexturedVertex[aiMesh->mNumVertices];

	for (size_t i = 0; i < aiMesh->mNumVertices; i++)
	{
		vert[i].x = aiMesh->mVertices[i].x;
		vert[i].y = aiMesh->mVertices[i].y;
		vert[i].z = aiMesh->mVertices[i].z;

		if (aiMesh->HasTextureCoords(0)){
			vert[i].u = aiMesh->mTextureCoords[0][i].x;
			vert[i].v = aiMesh->mTextureCoords[0][i].y;
		}
	}

	int indexCount = aiMesh->mNumFaces * 3;
	unsigned short* indices = new unsigned short[indexCount];
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		indices[i * 3 + 0] = aiMesh->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = aiMesh->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = aiMesh->mFaces[i].mIndices[2];
	}


	aiString path;
	aiString name;


	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
	{
		std::string texturePath;
		for (size_t i = path.length - 0; i > 0; i--)
		{
			if (path.data[i] == '/')
				break;
			texturePath = path.data[i] + texturePath;
		}
		texturePath = "Assets/Texture/" + texturePath;

		Texture tex = _render.loadTexture(texturePath, D3DCOLOR_XRGB(255, 255, 255));
		mesh->setTexture(tex);
		materialCount++;
	}

	mesh->setMeshData(vert, Primitive::TriangleList, aiMesh->mNumVertices, indices, indexCount);
}

