#pragma once

#include "GlobalHeader.h"
#include "SpriteLibrary.h"

#define TILE_GRID_OFFSET sf::Vector2f(500.0f, 50.0f)


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

