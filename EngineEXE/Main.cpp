#include "engine.h"
#include "pacman.h"
#include <time.h>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	/*AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);*/

	Engine eng(hInstance, 1024, 720);
	Game* a = new Pacman();
	eng.setGame(a);
	if (!eng.init()) return 1;

	eng.run();

	return 0;
}