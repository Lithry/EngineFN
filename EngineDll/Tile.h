#ifndef TILE_H
#define TILE_H

#include "Sprite.h"

#include "Export.h"

class DllExport Tile : public Sprite{
public:
	Tile();
	~Tile();
	
	bool isWalkable();
	void makeSolid(bool collidable);
	void setId(unsigned int id);
	unsigned int getId();
private:
	bool _collidable;
	unsigned int _id;
};
#endif

