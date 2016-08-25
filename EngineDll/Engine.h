#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "directinput.h"
#include "timer.h"

#define DllExport __declspec( dllexport )

using namespace std;

class DllExport Engine{
public:
	Engine(HINSTANCE hinst, unsigned int uiW, unsigned int uiH);
	~Engine();
	bool init();
	void run();
	void setGame(Game* a);
private:
	HINSTANCE hinstance;
	unsigned int uiWidth;
	unsigned int uiHeight;
	Window* w;
	Renderer* r;
	Game* g;
	DirectInput* i;
	Timer* t;
};
#endif