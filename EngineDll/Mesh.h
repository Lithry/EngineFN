#ifndef MESH_H
#define MESH_H

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

typedef TexturedVertex;
typedef Primitive;

class Renderer;
class VertexBuffer3D;
class IndexBuffer;

#define DllExport __declspec( dllexport )

class DllExport Mesh{
public:
	Mesh(Renderer& rkRenderer);
	~Mesh();

	void setMeshData(const TexturedVertex* pakVertices, Primitive ePrimitive,
		size_t uiVertexCount, const unsigned short* pusIndices,
		size_t uiIndexCount);
	void draw();
	void setTextureId(int iTextureId);

private:
	Renderer render;
	VertexBuffer3D* vertexBuffer;
	IndexBuffer* indexBuffer;

	std::vector<TexturedVertex> _textureVertex;
	std::vector<int> _index;
	Primitive _primitiv;
	size_t _vertexCount;
};
#endif