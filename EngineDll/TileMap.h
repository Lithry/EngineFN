#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include <string>

#include "Export.h"

class DllExport TileMap{
public:
	TileMap();
	~TileMap();

	const Tile& tile(unsigned int id);
	void setTile(const Tile& tile);
	void setMapTileId(int layer, unsigned int column, unsigned int row, unsigned int id);
	void makeGrid();

	void setDimensions(float width, float heigth);
	void setTileDimensions(float tileWidth, float tileHeigth);

	void setTexture(const Texture& texture);
	void draw(Renderer& renderer);

	bool importTileMap(std::string filePath, Renderer& renderer);
	void checkCollision(Entity2D& object);
private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;
	Texture _texture;
	unsigned int _width;
	unsigned int _height;
	float _tileWidth;
	float _tileHeight;
	float _imageWidth;
	float _imageHeight;
	std::string* _imagePath;
};
#endif

