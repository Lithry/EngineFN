#include "Importer.h"

#include <vector>
#include "Renderer.h"
#include "StructsAndEnums.h"
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
		vert[i].x = meshs->mVertices[i].x; // Set X Vert
		// Set X AABB
		if (mesher.getAABB().max.x < vert[i].x){ // MAX
			mesher.setBoundingBoxMaxX(vert[i].x);
		}
		else if (mesher.getAABB().min.x > vert[i].x){ // MIN
			mesher.setBoundingBoxMinX(vert[i].x);
		}
		vert[i].y = meshs->mVertices[i].y; // Set Y Vert
		// Set Y AABB
		if (mesher.getAABB().max.y < vert[i].y){ // MAX
			mesher.setBoundingBoxMaxY(vert[i].y);
		}
		else if (mesher.getAABB().min.y > vert[i].y){ // MIN
			mesher.setBoundingBoxMinY(vert[i].y);
		}
		vert[i].z = meshs->mVertices[i].z; // Set Z Vert
		// Set Z AABB
		if (mesher.getAABB().max.z < vert[i].z){ // MAX
			mesher.setBoundingBoxMaxZ(vert[i].z);
		}
		else if (mesher.getAABB().min.z > vert[i].z){ // MIN
			mesher.setBoundingBoxMinZ(vert[i].z);
		}

		if (meshs->HasTextureCoords(0)){
			vert[i].u = meshs->mTextureCoords[0][i].x;
			vert[i].v = - meshs->mTextureCoords[0][i].y;
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
	loadNode(root, orkSceneRoot, scene);

	return true;
}

void Importer::loadNode(aiNode* root, Node& node, const aiScene* scene){
	node.setName(root->mName.C_Str());

	aiVector3t<float> pos;
	aiVector3t<float> scale;
	aiQuaterniont<float> rotation;
	root->mTransformation.Decompose(scale, rotation, pos);

	node.setPos(pos.x, pos.y, pos.z);
	node.setScale(scale.x, scale.y, scale.z);
	node.setRotation(rotation.x, rotation.y, rotation.z);
	
	for (size_t i = 0; i < root->mNumMeshes; i++)
	{
		Mesh* newMesh = new Mesh(_render);
		node.addChild(newMesh);
		aiMesh* aiMesh = scene->mMeshes[root->mMeshes[i]];
		aiMaterial* pMaterial = scene->mMaterials[aiMesh->mMaterialIndex];

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
	mesh->setName(aiMesh->mName.C_Str());
	
	TexturedVertex* vert = new TexturedVertex[aiMesh->mNumVertices];

	for (size_t i = 0; i < aiMesh->mNumVertices; i++)
	{
		vert[i].x = aiMesh->mVertices[i].x; // Set X Vert
		// Set X AABB
		if (mesh->getAABB().max.x < vert[i].x){ // MAX
			mesh->setBoundingBoxMaxX(vert[i].x);
		}
		else if (mesh->getAABB().min.x > vert[i].x){ // MIN
			mesh->setBoundingBoxMinX(vert[i].x);
		}
		vert[i].y = aiMesh->mVertices[i].y; // Set Y Vert
		// Set Y AABB
		if (mesh->getAABB().max.y < vert[i].y){ // MAX
			mesh->setBoundingBoxMaxY(vert[i].y);
		}
		else if (mesh->getAABB().min.y > vert[i].y){ // MIN
			mesh->setBoundingBoxMinY(vert[i].y);
		}
		vert[i].z = aiMesh->mVertices[i].z; // Set Z Vert
		// Set Z AABB
		if (mesh->getAABB().max.z < vert[i].z){ // MAX
			mesh->setBoundingBoxMaxZ(vert[i].z);
		}
		else if (mesh->getAABB().min.z > vert[i].z){ // MIN
			mesh->setBoundingBoxMinZ(vert[i].z);
		}

		if (aiMesh->HasTextureCoords(0)){
			vert[i].u = aiMesh->mTextureCoords[0][i].x;
			vert[i].v = - aiMesh->mTextureCoords[0][i].y;
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

