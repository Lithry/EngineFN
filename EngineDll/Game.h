#ifndef GAME_H
#define GAME_H

#include <windows.h>

#include "Export.h"
//#define DllExport __declspec( dllexport )

class Renderer;
class Input;
class Timer;

class DllExport Game{
public:
	Game();
	virtual bool init(Renderer& rkRenderer) = 0;
	virtual void frame(Renderer& rkRenderer, Input& rkInputm, Timer& rkTimer) = 0;
	virtual void deinit() = 0;
	bool isDone() const;
	void setDone(bool bDone);
private:
	bool m_bDone;
};
#endif