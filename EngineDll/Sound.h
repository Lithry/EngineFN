#ifndef SOUND_H
#define SOUND_H
#include <string>

#define DLLexport __declspec(dllexport)
using namespace std;
class Sound
{
public:
	DLLexport Sound();
	DLLexport ~Sound();

	DLLexport bool open(std::string filePath, bool loop);
	DLLexport void play();
private:
	string _filePath;
	bool _loop;
};

#endif

