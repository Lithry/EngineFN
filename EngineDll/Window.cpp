#include "Window.h"

Window::Window(){
	title = new std::string;
}

Window::~Window(){
	delete title;
	title = NULL;
}

bool Window::init(HINSTANCE hInst, unsigned int uiWidth, unsigned int uiHeight){
	static TCHAR szWindowClass[] = _T("engine_fn");
	static TCHAR szTitle[] = _T("EngineFN");
	*title = szTitle;

	SetConsoleTitle(_T("Some title"));

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = szWindowClass;

	if (!RegisterClassEx(&wc)){
		MessageBox(NULL, _T("ClassEx Register failed!"), _T("EngineFN"), NULL);
		return false;
	}

	hWnd = CreateWindowEx(NULL,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		uiWidth, uiHeight,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!hWnd){
		MessageBox(NULL, _T("Window Create failed!"), _T("EnginFN"), NULL);
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}

void Window::setTitle(std::string title){
	SetWindowText(hWnd, title.c_str());
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}