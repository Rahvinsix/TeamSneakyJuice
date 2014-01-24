#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "SpriteLibrary.h"

#define MAP_SCREEN_WIDTH 400
#define MAP_SCREEN_HEIGHT 400

#define MAP_WIDTH 20
#define MAP_HEIGHT 10


class MapGrid
{
public:
	MapGrid(void);
	~MapGrid(void);

	void Draw(sf::RenderWindow*);

	void Click(sf::Event::MouseMoveEvent, int);

private:
	int** map;

	sf::FloatRect spriteSize;

};

