#pragma once

#include "GlobalHeader.h"
#include "SpriteLibrary.h"

#define TILE_GRID_OFFSET sf::Vector2f(400.0f, 570.0f)
#define GRID_WIDTH 5


class TileGrid
{
public:
	TileGrid(void);
	~TileGrid(void);

	void Draw(sf::RenderWindow*);

	void Click(sf::Event::MouseButtonEvent);

	int CurrentTile();


private:
	int _currentTile;
};

