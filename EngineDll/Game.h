#ifndef GAME_H
#define GAME_H

#include <windows.h>

#define DllExport __declspec( dllexport )

class Renderer;
class Input;
class Timer;

class Game{
public:
	DllExport Game();
	DllExport virtual bool init(Renderer& rkRenderer) = 0;
	DllExport virtual void frame(Renderer& rkRenderer, Input& rkInputm, Timer& rkTimer) = 0;
	DllExport virtual void deinit() = 0;
	DllExport bool isDone() const;
	DllExport void setDone(bool bDone);
private:
	bool m_bDone;
};
#endif