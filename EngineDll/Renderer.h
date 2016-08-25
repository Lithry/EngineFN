#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include <vector>
#include "vertexbuffer.h"

#define DllExport __declspec( dllexport )

class Vertex{
public:
	float x, y, z;
	DWORD color;
};
struct TexturedVertex{
public:
	float x, y, z;
	float u, v;
};
struct D3DXMATRIX;
typedef D3DXMATRIX* Matrix;
struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;
#define NoTexture NULL

typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

struct IDirect3D9;
struct IDirect3DDevice9;

//Se encarga de la comunicacion con el Direct3D
class DllExport Renderer{
public:
	Renderer();
	~Renderer();
	bool init(HWND hWnd, unsigned int uiW, unsigned int uiH);
	void beginFrame();
	void draw(Vertex gameVertex[]);
	void draw(TexturedVertex* gameVertex, int vertexCount);
	
	Font& createFont(int charSize, std::string textFont, bool italic);
	RECT& createRect(int x, int y, int width, int height);
	void displayText(Font& font, RECT& rect, std::string text);
	
	void endFrame();
	const Texture loadTexture(const std::string& textureName, D3DCOLOR iColorKey);
	void setCurrentTexture(const Texture& texture);
	void setMatrix(const Matrix& rkMatrix);
	int getWidth() const;
	int getHeigth() const;
	void setViewMatrix(D3DXMATRIX& viewMat);
private:
	HWND _hwnd;
	unsigned int uiWidth;
	unsigned int uiHeight;
	VertexBuffer* v_buffer;
	VertexBuffer* t_buffer;
	IDirect3D9* m_pkD3D;
	IDirect3DDevice9* m_pkDevice;
	std::vector<Texture> _textureList;
};
#endif