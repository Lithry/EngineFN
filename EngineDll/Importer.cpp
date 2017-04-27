#include "Importer.h"

#include <vector>
#include "Renderer.h"
#include "StructsAndEnums.h"
#include "Mesh.h"
#include "Node.h"
#include "BSP.h"
#include "AssImp\Importer.hpp"
#include "AssImp\scene.h"
#include "AssImp\postprocess.h"

#pragma comment(lib, "assimp.lib") 

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

Importer::Importer(Renderer& render)
	:
	_render(render),
	materialCount(0)
{}

Importer::~Importer() {

}

bool Importer::importMesh(const std::string& rkFilename, Mesh& mesher) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_Triangulate |
		aiProcess_MakeLeftHanded);

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
		if (mesher.getAABB().max.x < vert[i].x) { // MAX
			mesher.setBoundingBoxMaxX(vert[i].x);
		}
		else if (mesher.getAABB().min.x > vert[i].x) { // MIN
			mesher.setBoundingBoxMinX(vert[i].x);
		}
		vert[i].y = meshs->mVertices[i].y; // Set Y Vert
										   // Set Y AABB
		if (mesher.getAABB().max.y < vert[i].y) { // MAX
			mesher.setBoundingBoxMaxY(vert[i].y);
		}
		else if (mesher.getAABB().min.y > vert[i].y) { // MIN
			mesher.setBoundingBoxMinY(vert[i].y);
		}
		vert[i].z = meshs->mVertices[i].z; // Set Z Vert
										   // Set Z AABB
		if (mesher.getAABB().max.z < vert[i].z) { // MAX
			mesher.setBoundingBoxMaxZ(vert[i].z);
		}
		else if (mesher.getAABB().min.z > vert[i].z) { // MIN
			mesher.setBoundingBoxMinZ(vert[i].z);
		}

		if (meshs->HasTextureCoords(0)) {
			vert[i].u = meshs->mTextureCoords[0][i].x;
			vert[i].v = -meshs->mTextureCoords[0][i].y;
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

	mesher.polygons = meshs->mNumFaces;
	mesher.setMeshData(vert, Primitive::TriangleList, meshs->mNumVertices, indices, indexCount);

	return true;
}

bool Importer::importScene(const std::string& rkFilename, Node& orkSceneRoot) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_MakeLeftHanded);

	if (!scene)
	{
		const char* errors = importer.GetErrorString();
		return false;
	}

	aiNode* root = scene->mRootNode;
	loadNode(root, orkSceneRoot, scene);
	orkSceneRoot.setPos(0, 0, 0);
	orkSceneRoot.setScale(1, 1, 1);
	orkSceneRoot.setRotation(1, 0, 0, 0);

	return true;
}

bool Importer::importScene(const std::string& rkFilename, Node& orkSceneRoot, BSP* orkSceneBSP) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_MakeLeftHanded);

	if (!scene)
	{
		const char* errors = importer.GetErrorString();
		return false;
	}

	aiNode* root = scene->mRootNode;
	loadNode(root, orkSceneRoot, scene, orkSceneBSP);
	orkSceneRoot.setPos(0, 0, 0);
	orkSceneRoot.setScale(1, 1, 1);
	orkSceneRoot.setRotation(1, 0, 0, 0);

	return true;
}

void Importer::loadNode(aiNode* root, Node& node, const aiScene* scene) {
	node.setName(root->mName.C_Str());

	aiVector3t<float> pos;
	aiVector3t<float> scale;
	aiQuaterniont<float> rotation;
	root->mTransformation.Decompose(scale, rotation, pos);

	node.setPos(pos.x, pos.y, pos.z);
	node.setScale(scale.x, scale.y, scale.z);
	node.setRotation(rotation.w, rotation.x, rotation.y, rotation.z);
	


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

void Importer::loadNode(aiNode* root, Node& node, const aiScene* scene, BSP* bsp) {
	node.setName(root->mName.C_Str());
	
	std::string name = root->mName.C_Str();
	std::string chackPlane;
	for (size_t i = 0; i < name.length(); i++) {
		chackPlane += name[i];
		if (i == 4)
			break;
	}

	bool isPlane = chackPlane == "Plane" ? true : false;

	aiVector3t<float> pos;
	aiVector3t<float> scale;
	aiQuaterniont<float> rotation;
	aiMatrix4x4 transformationMat = root->mTransformation;
	root->mTransformation.Decompose(scale, rotation, pos);
	
	node.setPos(pos.x, pos.y, pos.z);
	node.setScale(scale.x, scale.y, scale.z);
	node.setRotation(rotation.w, rotation.x, rotation.y, rotation.z);
	Vec3 position;
	position.x = pos.x; position.y = pos.y; position.z = pos.z;
	Vec3 scal;
	scal.x = scale.x; scal.y = scale.y; scal.z = scale.z;
	Quaternion rot;
	rot.x = rotation.x; rot.y = rotation.y; rot.z = rotation.z; rot.w = rotation.w;

	for (size_t i = 0; i < root->mNumMeshes; i++) {
		Mesh* newMesh = new Mesh(_render);
		node.addChild(newMesh);
		aiMesh* aiMesh = scene->mMeshes[root->mMeshes[i]];
		aiMaterial* pMaterial = scene->mMaterials[aiMesh->mMaterialIndex];
		loadMesh(aiMesh, newMesh, pMaterial, isPlane, bsp, position, scal, rot);
	}

	for (size_t i = 0; i < root->mNumChildren; i++)	{
		Node* newNode = new Node();
		node.addChild(newNode);

		loadNode(root->mChildren[i], *newNode, scene, bsp);
	}
}

void Importer::loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material) {
	mesh->setName(aiMesh->mName.C_Str());

	mesh->polygons = aiMesh->mNumFaces;

	TexturedVertex* vert = new TexturedVertex[aiMesh->mNumVertices];

	for (size_t i = 0; i < aiMesh->mNumVertices; i++)
	{
		vert[i].x = aiMesh->mVertices[i].x; // Set X Vert
											// Set X AABB
		if (mesh->getAABB().max.x < vert[i].x) { // MAX
			mesh->setBoundingBoxMaxX(vert[i].x);
		}
		else if (mesh->getAABB().min.x > vert[i].x) { // MIN
			mesh->setBoundingBoxMinX(vert[i].x);
		}
		vert[i].y = aiMesh->mVertices[i].y; // Set Y Vert
											// Set Y AABB
		if (mesh->getAABB().max.y < vert[i].y) { // MAX
			mesh->setBoundingBoxMaxY(vert[i].y);
		}
		else if (mesh->getAABB().min.y > vert[i].y) { // MIN
			mesh->setBoundingBoxMinY(vert[i].y);
		}
		vert[i].z = aiMesh->mVertices[i].z; // Set Z Vert
											// Set Z AABB
		if (mesh->getAABB().max.z < vert[i].z) { // MAX
			mesh->setBoundingBoxMaxZ(vert[i].z);
		}
		else if (mesh->getAABB().min.z > vert[i].z) { // MIN
			mesh->setBoundingBoxMinZ(vert[i].z);
		}

		if (aiMesh->HasTextureCoords(0)) {
			vert[i].u = aiMesh->mTextureCoords[0][i].x;
			vert[i].v = -aiMesh->mTextureCoords[0][i].y;
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
		for (size_t i = path.length; i < -1; i--)
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

void Importer::loadMesh(aiMesh* aiMesh, Mesh* mesh, const aiMaterial* material, bool& isPlane, BSP* bsp, Vec3 position, Vec3 scale, Quaternion rotation) {
	mesh->setName(aiMesh->mName.C_Str());

	mesh->polygons = aiMesh->mNumFaces;

	TexturedVertex* vert = new TexturedVertex[aiMesh->mNumVertices];

	for (size_t i = 0; i < aiMesh->mNumVertices; i++)
	{
		vert[i].x = aiMesh->mVertices[i].x; // Set X Vert
											// Set X AABB
		if (mesh->getAABB().max.x < vert[i].x) { // MAX
			mesh->setBoundingBoxMaxX(vert[i].x);
		}
		else if (mesh->getAABB().min.x > vert[i].x) { // MIN
			mesh->setBoundingBoxMinX(vert[i].x);
		}
		vert[i].y = aiMesh->mVertices[i].y; // Set Y Vert
											// Set Y AABB
		if (mesh->getAABB().max.y < vert[i].y) { // MAX
			mesh->setBoundingBoxMaxY(vert[i].y);
		}
		else if (mesh->getAABB().min.y > vert[i].y) { // MIN
			mesh->setBoundingBoxMinY(vert[i].y);
		}
		vert[i].z = aiMesh->mVertices[i].z; // Set Z Vert
											// Set Z AABB
		if (mesh->getAABB().max.z < vert[i].z) { // MAX
			mesh->setBoundingBoxMaxZ(vert[i].z);
		}
		else if (mesh->getAABB().min.z > vert[i].z) { // MIN
			mesh->setBoundingBoxMinZ(vert[i].z);
		}

		if (aiMesh->HasTextureCoords(0)) {
			vert[i].u = aiMesh->mTextureCoords[0][i].x;
			vert[i].v = -aiMesh->mTextureCoords[0][i].y;
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
		for (size_t i = path.length; i < -1; i--)
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

	if (isPlane) {
		Vec3 v1;
		v1.x = aiMesh->mVertices[0].x; v1.y = aiMesh->mVertices[0].y; v1.z = aiMesh->mVertices[0].z;
		Vec3 v2;
		v2.x = aiMesh->mVertices[1].x; v2.y = aiMesh->mVertices[1].y; v2.z = aiMesh->mVertices[1].z;
		Vec3 v3;
		v3.x = aiMesh->mVertices[2].x; v3.y = aiMesh->mVertices[2].y; v3.z = aiMesh->mVertices[2].z;
		bsp->makePlane(v1, v2, v3, position, scale, rotation);
		
		bsp->addMesh(mesh);
		//loadPlane(bsp);
	}

	mesh->setMeshData(vert, Primitive::TriangleList, aiMesh->mNumVertices, indices, indexCount);
}

void Importer::loadPlane(BSP* bsp) {
	

	/*D3DXPLANE* plane = new D3DXPLANE();
	D3DXVECTOR3* vec1 = new D3DXVECTOR3(v1.x, v1.y, v1.z);
	D3DXVECTOR3* vec2 = new D3DXVECTOR3(v2.x, v2.y, v2.z);
	D3DXVECTOR3* vec3 = new D3DXVECTOR3(v3.x, v3.y, v3.z);
	D3DXPlaneFromPoints(plane, vec1, vec2, vec3);*/
}