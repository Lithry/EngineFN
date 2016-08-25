#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <tchar.h>
#include <string>

#define DllExport __declspec( dllexport )

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Se encarga de registrar y crear la ventana
class DllExport Window{
public:
	Window();
	~Window();
	bool init(HINSTANCE hInst, unsigned int uiWidth, unsigned int uiHeight);
	void Window::setTitle(std::string title);
	HWND hWnd; //Handler de la ventana
	std::string title;
private:
};
#endif