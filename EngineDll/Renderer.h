#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include "vertexbuffer.h"
#include <vector>

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

struct IDirect3D9;
struct IDirect3DDevice9;
struct D3DXMATRIX;
typedef D3DXMATRIX* Matrix;
struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;
#define NoTexture NULL

typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

//Se encarga de la comunicacion con el Direct3D
class Renderer{
public:
	DllExport Renderer();
	DllExport ~Renderer();
	DllExport bool init(HWND hWnd, unsigned int uiW, unsigned int uiH);
	DllExport void beginFrame();
	DllExport void draw(Vertex gameVertex[]);
	DllExport void draw(TexturedVertex* gameVertex, int vertexCount);
	
	DllExport Font& createFont(int charSize, std::string textFont, bool italic);
	DllExport RECT& createRect(int x, int y, int width, int height);
	DllExport void displayText(Font& font, RECT& rect, std::string text);
	
	DllExport void endFrame();
	DllExport const Texture loadTexture(const std::string& textureName, D3DCOLOR iColorKey);
	DllExport void setCurrentTexture(const Texture& texture);
	DllExport void setMatrix(const Matrix& rkMatrix);
	DllExport int getWidth() const;
	DllExport int getHeigth() const;
	DllExport void setViewMatrix(D3DXMATRIX& viewMat);
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