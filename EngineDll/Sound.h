#ifndef SOUND_H
#define SOUND_H

#include <string>

#include "Export.h"

using namespace std;

class DllExport Sound{
public:
	Sound();
	~Sound();

	bool open(std::string filePath, bool loop);
	void play();
private:
	string _filePath;
	bool _loop;
};

#endif

