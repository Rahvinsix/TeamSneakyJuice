#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "SpriteLibrary.h"
#include <string>
#include <fstream>

#define MAP_SCREEN_WIDTH 1200
#define MAP_SCREEN_HEIGHT 550


class MapGrid
{
public:
	MapGrid(std::string fileName, int width, int height);
	~MapGrid(void);

	void Draw(sf::RenderWindow*);

	void Click(int, int, int);

private:
	int** map;

	sf::FloatRect spriteSize;

	std::string _fileName;

	int _mapWidth;
	int _mapHeight;

};

