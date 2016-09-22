#include "Renderer.h"

#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)

D3DPRIMITIVETYPE Primitives[Primitive::PrimitiveCount] = { D3DPT_POINTLIST,
															D3DPT_LINELIST,
															D3DPT_LINESTRIP,
															D3DPT_TRIANGLELIST,
															D3DPT_TRIANGLESTRIP,
															D3DPT_TRIANGLEFAN };

Renderer::Renderer(){}

Renderer::~Renderer(){
	m_pkDevice->Release();
	m_pkDevice = NULL;
	m_pkD3D->Release();
	m_pkD3D = NULL;

	delete v3D_buffer;
	v3D_buffer = NULL;
	delete i3D_buffer;
	i3D_buffer = NULL;

	std::vector<Texture>::iterator iter;
	for (iter = _textureList.begin(); iter != _textureList.end(); iter++){
		(*iter)->Release();
		(*iter) = NULL;
	}

	_textureList.clear();
}

bool Renderer::init(HWND hWnd, unsigned int uiW, unsigned int uiH){
	_hwnd = hWnd;
	uiWidth = uiW;
	uiHeight = uiH;

	m_pkD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_pkD3D) return false;

	D3DDISPLAYMODE displayMode;
	HRESULT hr;
	hr = m_pkD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if (hr != D3D_OK) return false;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = displayMode.Format;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	hr = m_pkD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pkDevice);

	if (hr != D3D_OK) return false;

	D3DXMATRIX matProjection;

	D3DXMatrixPerspectiveFovLH(&matProjection,
		(D3DX_PI*0.25),
		float(uiW) / float(uiH),
		1.0f,
		10000.0f);

	m_pkDevice->SetTransform(D3DTS_PROJECTION, &matProjection);

	//v_buffer = new VertexBuffer(m_pkDevice, sizeof(Vertex), CUSTOMFVF);
	//t_buffer = new VertexBuffer(m_pkDevice, sizeof(TexturedVertex), TEXTUREFVF);

	// Enable Z-Buffer
	m_pkDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	// Apagar Luces
	m_pkDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pkDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Alpha
	m_pkDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pkDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pkDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pkDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	return true;
}

void Renderer::beginFrame(){
	m_pkDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_pkDevice->BeginScene();
}

void Renderer::draw(Vertex gameVertex[]){
	//v_buffer->bind();
	//v_buffer->draw(gameVertex, D3DPT_TRIANGLESTRIP, 4);
}

void Renderer::draw(TexturedVertex* gameVertex, int vertexCount){
	//t_buffer->bind();
	//t_buffer->draw(gameVertex, D3DPT_TRIANGLESTRIP, vertexCount);
}

Font& Renderer::createFont(int charSize, std::string textFont, bool italic){
	Font font;
	D3DXCreateFont(m_pkDevice, 
				   charSize, 
				   0, 
				   FW_NORMAL, 
				   1, italic, 
				   DEFAULT_CHARSET, 
				   OUT_DEFAULT_PRECIS, 
				   ANTIALIASED_QUALITY, 
				   FF_DONTCARE,
				   textFont.c_str(),
				   &font);

	return font;
}

RECT& Renderer::createRect(int x, int y, int width, int height){
	RECT rect;
	SetRect(&rect, x, y, width, height);

	return rect;
}

void Renderer::displayText(Font& font, RECT& rect, std::string text){
	font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255,255,255));
}

void Renderer::endFrame(){
	m_pkDevice->EndScene();
	m_pkDevice->Present(NULL, NULL, NULL, NULL);
}

void Renderer::setMatrix(const Matrix& rkMatrix){
	m_pkDevice->SetTransform(D3DTS_WORLD, rkMatrix);
}

const Texture Renderer::loadTexture(const std::string& textureName, D3DCOLOR iColorKey){
	Texture texture = NULL;

	D3DXCreateTextureFromFileEx(m_pkDevice,
		textureName.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		iColorKey,
		NULL,
		NULL,
		&texture);

	if (texture){
		_textureList.push_back(texture);
		return texture;
	}

	else{
		MessageBox(_hwnd, "No Texture", "No Texture", MB_OK);
		return NULL;
	}
}

void Renderer::setCurrentTexture(const Texture& texture){
	m_pkDevice->SetTexture(0, texture);
}
int Renderer::getWidth() const{
	return uiWidth;
}

int Renderer::getHeigth() const{
	return uiHeight;
}

void Renderer::setViewMatrix(D3DXMATRIX& viewMat){
	m_pkDevice->SetTransform(D3DTS_VIEW, &viewMat);
}

VertexBuffer3D* Renderer::createVertexBuffer(size_t uiVertexSize, unsigned int uiFVF){
	VertexBuffer3D* vBuffer = new VertexBuffer3D(*this, m_pkDevice, uiVertexSize, uiFVF);
	return vBuffer;
}

IndexBuffer* Renderer::createIndexBuffer(){
	IndexBuffer* iBuffer = new IndexBuffer(*this, m_pkDevice);
	return iBuffer;
}

void Renderer::setCurrentIndexBuffer(IndexBuffer* pkIndexBuffer){
	i3D_buffer = pkIndexBuffer;
}

void Renderer::setCurrentVertexBuffer(VertexBuffer3D* pkVertexBuffer){
	v3D_buffer = pkVertexBuffer;
}

void Renderer::drawCurrentBuffers(Primitive ePrimitive){
	i3D_buffer->bind();
	v3D_buffer->bind();
	int iPrimitiveCount = 0;

	if (Primitives[ePrimitive] == D3DPT_POINTLIST){
		iPrimitiveCount = i3D_buffer->indexCount();
	}
	else if (Primitives[ePrimitive] == D3DPT_LINELIST){
		iPrimitiveCount = i3D_buffer->indexCount() / 2;
	}
	else if (Primitives[ePrimitive] == D3DPT_LINESTRIP){
		iPrimitiveCount = i3D_buffer->indexCount() - 1;
	}
	else if (Primitives[ePrimitive] == D3DPT_TRIANGLELIST){
		iPrimitiveCount = i3D_buffer->indexCount() / 3;
	}
	else if (Primitives[ePrimitive] == D3DPT_TRIANGLESTRIP){
		iPrimitiveCount = i3D_buffer->indexCount() - 2;
	}
	else if (Primitives[ePrimitive] == D3DPT_TRIANGLEFAN){
		iPrimitiveCount = i3D_buffer->indexCount() - 2;
	}
	
	m_pkDevice->DrawIndexedPrimitive(Primitives[ePrimitive], 0, 0,
		v3D_buffer->vertexCount(), 0, iPrimitiveCount);
}
