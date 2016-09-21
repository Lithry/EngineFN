#ifndef SCREENTEXT_H
#define SCREENTEXT_H
//====================================
#include <string>
#include "Renderer.h"
//===================================================================
#define DllExport __declspec(dllexport)
//===================================================================
class DllExport ScreenText{
public:
	ScreenText();
	~ScreenText();

	void create(int x, int y, 
			  int width, int height,
			  int charSize,
			  std::string textFont, std::string text,
			  bool italic,
			  Renderer& renderer);

	void display(Renderer& renderer);

	void setText(std::string text);
private:
	Font _font;
	int _width, _height;
	int _charSize;
	int _x, _y;
	bool _italic;
	std::string* _textFont;
	RECT _rect;
	std::string* _text;
};
//===================================================================
#endif

