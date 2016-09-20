#include "Engine.h"
#include <sstream>

Engine::Engine(HINSTANCE hinst, unsigned int uiW, unsigned int uiH)
	:
	w(new Window()),
	r(new Renderer()),
	g(NULL),
	i(new DirectInput()),
	t(new Timer()),
	hinstance(hinst),
	uiWidth(uiW),
	uiHeight(uiH)
{}

Engine::~Engine(){
	delete t;
	t = NULL;
	delete g;
	g = NULL;
	delete i;
	i = NULL;
	delete r;
	r = NULL;
	delete w;
	w = NULL;
}

bool Engine::init(){
	if (!w->init(hinstance, uiWidth, uiHeight))
		return false;
	if (!r->init(w->hWnd, uiWidth, uiHeight))
		return false;
	if (!i->init(hinstance, w->hWnd))
		return false;
	if (!g->init(*r))
		return false;
	/*if (!t)
		t->firstMeasure();
		else
		return false;*/

	return true;
}

void Engine::run(){
	MSG Msg;
	t->firstMeasure();
	while (!g->isDone())
	{
		static std::stringstream showFps;
		showFps.str("");
		showFps << "EngineFN (" << t->fps() << " FPS)";
		w->setTitle(showFps.str());

		i->reacquire();
		r->beginFrame();
		g->frame(*r, *i, *t);
		t->measure();
		r->endFrame();

		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)){
			switch (Msg.message){
			case WM_QUIT:
				g->setDone(true);
				break;
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	g->deinit();
}

void Engine::setGame(Game* a){
	g = a;
}